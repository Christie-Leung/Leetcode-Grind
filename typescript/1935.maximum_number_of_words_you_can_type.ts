/**
 * Link: https://leetcode.com/problems/maximum-number-of-words-you-can-type/description
 * Tags: String
 * Difficulty: Easy
 * Date: 2025-09-15
 */

function canBeTypedWords(text: string, brokenLetters: string): number {

    if (brokenLetters.length == 0) return text.split(" ").length;
    const words: string[] = text.split(" ");
    const regex = new RegExp(brokenLetters.replace(/./g, '|$&').substr(1));

    let valid = 0;
    for (let w of words) {
        if (!regex.test(w)) {
            valid += 1;
        }
    }

    return valid;
};