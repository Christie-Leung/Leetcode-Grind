#!/usr/bin/env python3
"""
Generates README.md with:
- totals, streaks,
- pastel transparent language pie chart,
- 12-month calendar heatmap,
- XP/Level + progress bar,
- achievements,
- TAG CLOUD (from comment lines like "tag: DP, Array, Graph").

Run:
  python scripts/generate_readme.py
"""
from __future__ import annotations
import os
import re
import sys
import json
import math
import random
import pathlib
from datetime import date, datetime, timedelta
from collections import Counter, defaultdict

ROOT = pathlib.Path(__file__).resolve().parents[1]
ASSETS = ROOT / "assets"
ASSETS.mkdir(exist_ok=True)
TEMPLATE = ROOT / "scripts" / "README.template.md"
OUTPUT = ROOT / "README.md"
PIE_PATH = ASSETS / "lang_pie.png"
HEATMAP_PATH = ASSETS / "heatmap.png"
TAGS_PATH = ASSETS / "tags_cloud.png"

LANG_HINTS = {
    "py": "Python", "python": "Python",
    "cpp": "C++", "c": "C",
    "cs": "C#", "csharp": "C#",
    "java": "Java",
    "js": "JavaScript", "ts": "TypeScript",
    "rust": "Rust", "rs": "Rust",
    "go": "Go", "swift": "Swift",
    "kt": "Kotlin", "kotlin": "Kotlin",
    "rb": "Ruby", "php": "PHP", "scala": "Scala",
}

IGNORED_FOLDERS = {
    ".git", ".github", "assets", "scripts", "node_modules",
    ".venv", "venv", "__pycache__", ".idea", ".vscode"
}

URL_RE = re.compile(r"https?://leetcode\.com/\S+", re.IGNORECASE)
DIFF_RE = re.compile(r"Difficulty\s*:\s*(Easy|Medium|Hard)", re.IGNORECASE)

DATE_CANDIDATE_RE = re.compile(
    r"""
    (?:
        (?P<iso>\b\d{4}[-/.]\d{1,2}[-/.]\d{1,2}\b) |
        (?P<dmy>\b\d{1,2}[-/.]\d{1,2}[-/.]\d{4}\b) |
        (?P<mdy>\b\d{1,2}[-/.]\d{1,2}[-/.]\d{2,4}\b) |
        (?P<long>\b(?:Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)[a-z]*\s+\d{1,2},?\s+\d{4}\b)
    )
    """,
    re.IGNORECASE | re.VERBOSE,
)

TAGS_LINE_RE = re.compile(r"^\s*Tags?\s*:\s*(.+)$", re.IGNORECASE | re.MULTILINE)

XP_BY_DIFF = {"easy": 10, "medium": 20, "hard": 30}
DEFAULT_XP = 10

MAX_TAGS = 60
TAG_MIN_SIZE = 12
TAG_MAX_SIZE = 48
TAG_STOPWORDS = {
    "and","or","the","a","an","to","of","by","for","in","on","with",
}
TAG_SYNONYMS = {
    "dp": "dynamic programming",
    "two pointers": "two-pointers",
    "two-pointers": "two-pointers",
    "sliding window": "sliding-window",
    "prefix sum": "prefix-sum",
    "binary search": "binary-search",
    "union find": "union-find",
    "disjoint set": "union-find",
    "linked list": "linked-list",
    "bitmask": "bitmasking",
    "bit manipulation": "bit-manipulation",
    "bfs": "bfs",
    "dfs": "dfs",
    "graph": "graph",
    "graphs": "graph",
    "tree": "tree",
    "trie": "trie",
    "heap": "heap",
    "priority queue": "heap",
    "stack": "stack",
    "queue": "queue",
    "greedy": "greedy",
    "math": "math",
    "array": "array",
    "strings": "string",
    "string": "string",
    "hash map": "hash-map",
    "hashmap": "hash-map",
    "map": "hash-map",
    "set": "set",
    "geometry": "geometry",
    "simulation": "simulation",
    "backtracking": "backtracking",
    "recursion": "recursion",
    "combinatorics": "combinatorics",
    "design": "design",
}

def parse_date_any(s: str) -> date | None:
    s = s.strip()
    fmts = ("%Y-%m-%d", "%Y/%m/%d", "%Y.%m.%d",
            "%d-%m-%Y", "%d/%m/%Y", "%d.%m.%Y",
            "%m-%d-%Y", "%m/%d/%Y", "%m.%d.%Y",
            "%b %d %Y", "%b %d, %Y", "%B %d %Y", "%B %d, %Y")
    for fmt in fmts:
        try:
            return datetime.strptime(s, fmt).date()
        except ValueError:
            pass
    s2 = s.replace(",", "")
    for fmt in ("%b %d %Y", "%B %d %Y"):
        try:
            return datetime.strptime(s2, fmt).date()
        except ValueError:
            pass
    return None

def extract_info(fp: pathlib.Path):
    """Return (attempt_date, difficulty, url, tags:list[str]) if found."""
    try:
        text = fp.read_text(encoding="utf-8", errors="ignore")
    except Exception:
        return None, None, None, []

    d = None
    for m in DATE_CANDIDATE_RE.finditer(text):
        d = parse_date_any(m.group(0))
        if d:
            break

    diff = None
    m = DIFF_RE.search(text)
    if m:
        diff = m.group(1).lower()

    url = None
    m = URL_RE.search(text)
    if m:
        url = m.group(0)

    tags: list[str] = []
    for line in TAGS_LINE_RE.findall(text):
        parts = re.split(r"[;,]", line)
        for p in parts:
            tag = normalize_tag(p)
            if tag:
                tags.append(tag)

    return d, diff, url, tags

def normalize_tag(s: str) -> str | None:
    t = s.strip().lower()
    t = re.sub(r"[^\w+#\- ]+", " ", t)
    t = re.sub(r"\s+", " ", t).strip()

    if not t or t in TAG_STOPWORDS:
        return None
    
    t = t.replace("_", " ")

    t = TAG_SYNONYMS.get(t, t)

    return t

def compute_streaks(sorted_unique_days):
    if not sorted_unique_days:
        return 0, 0, None
    longest = cur = 1
    for i in range(1, len(sorted_unique_days)):
        if sorted_unique_days[i] == sorted_unique_days[i-1] + timedelta(days=1):
            cur += 1
            longest = max(longest, cur)
        else:
            cur = 1
    last = sorted_unique_days[-1]
    cur2 = 1
    for i in range(len(sorted_unique_days)-2, -1, -1):
        if sorted_unique_days[i] == sorted_unique_days[i+1] - timedelta(days=1):
            cur2 += 1
        else:
            break
    return cur2, longest, last

def human_date(d: date | None) -> str:
    return d.strftime("%Y-%m-%d") if d else "N/A"


def pastel_colors(n: int):
    palette = [
        "#A8D8EA", "#BDE0FE", "#CDEAC0", "#FFD6A5", "#FFADAD", "#E5D4EF",
        "#B8E0D2", "#FDE2E4", "#F1F7B5", "#D7E3FC", "#CDE1F9", "#F6DFEB",
    ]
    return [palette[i % len(palette)] for i in range(n)]

def make_pie(lang_counts: dict[str, int], out_path: pathlib.Path) -> None:
    import matplotlib.pyplot as plt
    import matplotlib.patheffects as pe

    out_path.parent.mkdir(exist_ok=True, parents=True)
    total = sum(lang_counts.values())
    fig, ax = plt.subplots()
    fig.patch.set_alpha(0)
    ax.set_facecolor("none")

    if total == 0:
        t = ax.text(0.5, 0.5, "No data yet", ha="center", va="center",
                    fontsize=14, color="white", weight="bold")
        t.set_path_effects([pe.withStroke(linewidth=2, foreground="black")])
        ax.axis("off")
        plt.savefig(out_path, bbox_inches="tight", dpi=200, transparent=True)
        plt.close(fig)
        return

    labels = list(lang_counts.keys())
    sizes  = [lang_counts[k] for k in labels]
    colors = pastel_colors(len(labels))
    zero_color = "#464646"

    def color_for(c: int):
        if c <= 0:
            return zero_color
        if maxc <= 1:
            return pastel[-1]
        # map 1..maxc -> 0..levels-1
        idx = min(levels - 1, max(0, math.ceil(c * levels / maxc) - 1))
        return pastel[idx]

    wedges, texts, autotexts = ax.pie(
        sizes, labels=labels, colors=colors,
        autopct="%1.1f%%", startangle=140,
        textprops={"color": "white", "weight": "bold"},
        pctdistance=0.7,
        wedgeprops={"linewidth": 0.0, "edgecolor": "none"},
    )
    import matplotlib.patheffects as pe2
    for t in texts + autotexts:
        t.set_path_effects([pe2.withStroke(linewidth=2, foreground="black")])
    ax.axis("equal")
    plt.savefig(out_path, bbox_inches="tight", dpi=200, transparent=True)
    plt.close(fig)

def make_heatmap(daily_counts: dict[date, int], out_path: pathlib.Path) -> None:
    """
    53x7 grid like GitHub, covering last 365 days up to today.
    - 0 solves  -> light grey box
    - >0 solves -> pastel intensity
    """
    import matplotlib.pyplot as plt
    import matplotlib.patches as patches
    from math import ceil

    today = date.today()
    start = today - timedelta(days=364)

    # Build timeline
    days = [start + timedelta(days=i) for i in range(365)]
    counts = [daily_counts.get(d, 0) for d in days]
    maxc = max(counts) if counts else 0

    # Colors
    pastels = [
       "#BDE0FE","#E5D4EF", "#F6DFEB",
    ]
    intensities = [pastels[i % len(pastels)] for i in range(3)]
    ZERO_COLOR = "#313131BE" 

    def color_for(c: int):
        if c <= 0:
            return ZERO_COLOR
        if maxc <= 1:
            return intensities[0]
        # 1..maxc -> 0..3
        idx = min(3, max(0, ceil(c * 3 / maxc) - 1))
        return intensities[idx]

    # Layout
    start_weekday = start.weekday()  # Mon=0..Sun=6
    cell = 10
    pad = 2
    weeks = 53
    width = weeks * (cell + pad) + pad
    height = 7 * (cell + pad) + pad

    fig = plt.figure(figsize=(width/50, height/50), dpi=200)
    ax = fig.add_subplot(111)
    fig.patch.set_alpha(0)      # transparent background
    ax.set_facecolor("none")
    ax.set_xlim(0, width)
    ax.set_ylim(0, height)
    ax.axis("off")

    # Draw boxes
    for d in days:
        delta = (d - start).days
        week = (start_weekday + delta) // 7
        dow = (start_weekday + delta) % 7  # 0..6 Mon..Sun
        x = pad + week * (cell + pad)
        y = pad + (6 - dow) * (cell + pad)  # top row is Sunday
        rect = patches.Rectangle(
            (x, y), cell, cell,
            linewidth=0,
            edgecolor=None,
            facecolor=color_for(daily_counts.get(d, 0)),
        )
        ax.add_patch(rect)

    plt.savefig(out_path, bbox_inches="tight", dpi=200, transparent=True)
    plt.close(fig)
def make_tag_cloud(tag_freq: dict[str, int], out_path: pathlib.Path) -> None:
    """
    Simple tag cloud renderer (no external deps).
    - Scales font size between TAG_MIN_SIZE..TAG_MAX_SIZE.
    - Random pastel colors per tag.
    - Spiral placement with basic collision avoidance.
    """
    import matplotlib.pyplot as plt
    import matplotlib.patheffects as pe
    from matplotlib.transforms import Bbox

    # keep top N
    items = sorted(tag_freq.items(), key=lambda kv: kv[1], reverse=True)[:MAX_TAGS]
    if not items:
        # output a blank "No tags yet" image
        fig, ax = plt.subplots(figsize=(6, 3), dpi=200)
        fig.patch.set_alpha(0)
        ax.set_facecolor("none")
        t = ax.text(0.5, 0.5, "No tags yet", ha="center", va="center",
                    fontsize=14, color="white", weight="bold")
        t.set_path_effects([pe.withStroke(linewidth=2, foreground="black")])
        ax.axis("off")
        plt.savefig(out_path, bbox_inches="tight", dpi=200, transparent=True)
        plt.close(fig)
        return

    # Normalize sizes
    counts = [c for _, c in items]
    cmin, cmax = min(counts), max(counts)
    def scale(c):
        if cmax == cmin:
            return (TAG_MIN_SIZE + TAG_MAX_SIZE) // 2
        return int(TAG_MIN_SIZE + (TAG_MAX_SIZE - TAG_MIN_SIZE) * ((c - cmin) / (cmax - cmin)))

    random.seed(42)
    colors = pastel_colors(len(items))

    # Canvas
    W, H = 1000, 500  
    fig, ax = plt.subplots(figsize=(W/200, H/200), dpi=200)
    fig.patch.set_alpha(0)
    ax.set_facecolor("none")
    ax.set_xlim(0, W)
    ax.set_ylim(0, H)
    ax.axis("off")

    placed: list[Bbox] = []

    def collides(bb: Bbox) -> bool:
        pad = 4.0
        bb2 = Bbox.from_extents(bb.x0 - pad, bb.y0 - pad, bb.x1 + pad, bb.y1 + pad)
        for other in placed:
            if (bb2.x0 < other.x1 and bb2.x1 > other.x0 and
                bb2.y0 < other.y1 and bb2.y1 > other.y0):
                return True
        return False

    # Spiral placement around center
    cx, cy = W/2, H/2
    angle_step = 0.35
    radius_step = 3.5

    for i, (tag, cnt) in enumerate(items):
        fs = scale(cnt)
        color = colors[i % len(colors)]
        angle = 0.0
        radius = 0.0
        placed_ok = False
        for _ in range(300):
            x = cx + radius * math.cos(angle)
            y = cy + radius * math.sin(angle)
            # create text and measure bbox
            t = ax.text(x, y, tag,
                        ha="center", va="center",
                        fontsize=fs, color="white", weight="bold",
                        rotation=0, zorder=2)
            t.set_path_effects([pe.withStroke(linewidth=2, foreground="black")])
            # color fill via outline + colored shadow
            t.set_color(color)

            fig.canvas.draw()  # update text size
            bb = t.get_window_extent(renderer=fig.canvas.get_renderer())
            # transform display bbox to data coords
            inv = ax.transData.inverted()
            bb_data = Bbox(inv.transform(bb))
            # check bounds and collisions
            if (0 <= bb_data.x0 and bb_data.x1 <= W and
                0 <= bb_data.y0 and bb_data.y1 <= H and
                not collides(bb_data)):
                placed.append(bb_data)
                placed_ok = True
                break
            # not placed -> remove and try next offset
            t.remove()
            angle += angle_step
            radius += radius_step

        if not placed_ok:
            # fallback: skip if cannot place nicely
            pass

    plt.savefig(out_path, bbox_inches="tight", dpi=200, transparent=True)
    plt.close(fig)


def compute_xp(difficulty: str | None) -> int:
    if not difficulty:
        return DEFAULT_XP
    return XP_BY_DIFF.get(difficulty.lower(), DEFAULT_XP)

def level_for(xp: int):
    level = xp // 100
    next_level_xp = (level + 1) * 100
    into = xp - level * 100
    return level, into, next_level_xp

def progress_bar(current: int, target: int, width=24) -> str:
    pct = 0.0 if target == 0 else current / target
    filled = round(width * pct)
    return f"[{'█'*filled}{'░'*(width-filled)}] {int(pct*100)}%"

def make_badges(total: int, current_streak: int, longest_streak: int,
                langs_count: int, level: int) -> str:
    badges = []
    if total >= 10: badges.append("🥉 **10 Problems**")
    if total >= 50: badges.append("🥈 **50 Problems**")
    if total >= 100: badges.append("🥇 **100 Problems**")
    if total >= 250: badges.append("🏅 **250 Problems**")
    if total >= 500: badges.append("🏆 **500 Problems**")
    if current_streak >= 7: badges.append("🔥 **7-Day Current Streak**")
    if current_streak >= 30: badges.append("🔥🔥 **30-Day Current Streak**")
    if longest_streak >= 30: badges.append("⏱️ **30-Day Longest Streak**")
    if longest_streak >= 100: badges.append("⏱️⏱️ **100-Day Longest Streak**")
    if langs_count >= 2: badges.append("🧠 **Multi-Lingual Solver (2+)**")
    if langs_count >= 3: badges.append("🧩 **Tri-Lingual Solver (3+)**")
    if level >= 5: badges.append("🚀 **Level 5+**")
    if level >= 10: badges.append("🌟 **Level 10+**")
    if not badges:
        badges = ["🌱 Keep going — first milestones unlock soon!"]
    return "\n".join(f"- {b}" for b in badges)


def main() -> int:
    if not TEMPLATE.exists():
        print(f"Missing template: {TEMPLATE}", file=sys.stderr)
        return 2

    lang_counts: Counter[str] = Counter()
    unique_problem_names: set[str] = set()
    daily_counts: Counter[date] = Counter()
    total_xp = 0
    tag_freq: Counter[str] = Counter()

    for child in ROOT.iterdir():
        if not child.is_dir():
            continue
        if child.name in IGNORED_FOLDERS:
            continue

        lang_label = LANG_HINTS.get(child.name.lower(), child.name)
        for fp in child.rglob("*"):
            if not fp.is_file() or fp.name.startswith("."):
                continue
            if fp.suffix.lower() in (".md", ".png", ".jpg", ".jpeg", ".gif", ".svg", ".txt"):
                continue

            unique_problem_names.add(fp.stem)
            lang_counts[lang_label] += 1

            d, difficulty, _url, tags = extract_info(fp)
            if d:
                daily_counts[d] += 1
                total_xp += compute_xp(difficulty)

            for t in tags:
                tag_freq[t] += 1

    unique_days_sorted = sorted(daily_counts.keys())
    current_streak, longest_streak, last_date = compute_streaks(unique_days_sorted)
    
    make_pie(dict(lang_counts), PIE_PATH)
    make_heatmap(daily_counts, HEATMAP_PATH)
    make_tag_cloud(tag_freq, TAGS_PATH)

    
    level, into, next_level_xp = level_for(total_xp)
    bar = progress_bar(into, next_level_xp - level*100)
    badges_md = make_badges(
        total=len(unique_problem_names),
        current_streak=current_streak,
        longest_streak=longest_streak,
        langs_count=len(lang_counts),
        level=level,
    )

    rows = []
    for child in ROOT.iterdir():
        if not child.is_dir() or child.name in IGNORED_FOLDERS:
            continue
        lang_label = LANG_HINTS.get(child.name.lower(), child.name)
        for fp in child.rglob("*"):
            if not fp.is_file() or fp.name.startswith("."):
                continue
            if fp.suffix.lower() in (".md", ".png", ".jpg", ".jpeg", ".gif", ".svg", ".txt"):
                continue

            d, difficulty, url, tags = extract_info(fp)
            rel_path = fp.relative_to(ROOT)
            problem_name = fp.stem.replace("_"," ").replace("."," ").title()
            date_str = human_date(d)
            rows.append((d, date_str, problem_name, lang_label, url, rel_path))

    rows.sort(key=lambda r: (r[0] or date.min), reverse=True)

    table_lines = []
    table_lines.append("| Date | Problem | Language | Solution |")
    table_lines.append("|------|---------|----------|----------|")
    for _d, date_str, problem_name, lang_label, url, rel_path in rows:
        problem_cell = f"[{problem_name}]({url})" if url else problem_name
        solution_cell = f"[📄]({rel_path.as_posix()})"
        table_lines.append(
            f"| {date_str} | {problem_cell} | {lang_label} | {solution_cell} |"
        )
    table_md = "\n".join(table_lines)



    tmpl = TEMPLATE.read_text(encoding="utf-8")
    filled = (
        tmpl.replace("{{TOTAL}}", str(len(unique_problem_names)))
            .replace("{{CURRENT_STREAK}}", str(current_streak))
            .replace("{{LONGEST_STREAK}}", str(longest_streak))
            .replace("{{LAST_DATE}}", human_date(last_date))
            .replace("{{LEVEL}}", str(level))
            .replace("{{XP}}", str(total_xp))
            .replace("{{NEXT_LEVEL_XP}}", str(next_level_xp))
            .replace("{{PROGRESS_BAR}}", bar)
            .replace("{{BADGES}}", badges_md)
            .replace("{{TABLE}}", table_md)
    )

    OUTPUT.write_text(filled, encoding="utf-8")
    print(f"Updated {OUTPUT.relative_to(ROOT)}")
    print(f"Wrote {PIE_PATH.relative_to(ROOT)}, {HEATMAP_PATH.relative_to(ROOT)}, {TAGS_PATH.relative_to(ROOT)}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
