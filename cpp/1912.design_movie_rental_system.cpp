/**
 * Link: https://leetcode.com/problems/implement-router/description
 * Tags: Design, Hash Table, Ordered Set 
 * Difficulty: Hard
 * Date: 2025-09-21
 */

// didn't pass all test cases (time limit exceeded)

#include <map>
#include <set>
#include <vector>
using namespace std;

class MovieRentingSystem {
public:
    map<long long, vector<int>> allMovies;
    map<long long, long long> rentalStrings;
    map<int, set<long long>> byMovies;
    set<long long> rented;

    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (int i = 0; i < entries.size(); i++) {
            long long key = getKey(entries[i]);

            allMovies.insert({key, entries[i]});
            int movie = entries[i][1];
            byMovies[movie].insert(key);
            rentalStrings.insert({getRentKey(entries[i][0], movie), key});
        }
    }
    
    vector<int> search(int movie) {
        set<long long> shops = byMovies[movie];
        
        int movies = 0;
        vector<int> ans;
        for (auto it = shops.begin(); it != shops.end(); it++) {
            long long key = *it;
            if (rented.count(key)) continue;
            ans.push_back(allMovies[key][0]);
            if (++movies == 5) break;
        }

        return ans;
    }
    
    void rent(int shop, int movie) {
        long long rentKey = getRentKey(shop, movie);
        rented.insert(rentalStrings[rentKey]);
    }
    
    void drop(int shop, int movie) {
        long long rentKey = getRentKey(shop, movie);
        rented.erase(rentalStrings[rentKey]);
    }
    
    vector<vector<int>> report() {
        int movies = 0;
        vector<vector<int>> rep;
        for (auto it = rented.begin(); it != rented.end(); it++) {
            rep.push_back({allMovies[*it][0], allMovies[*it][1]});
            movies++;
            if (movies == 5) break;
        }
        return rep;
    }

    long long getKey(vector<int> entry) {
        return ((long long) entry[2] << 40) | ((long long) entry[0] << 20) | entry[1];
    }

    long long getRentKey(int shop, int movie) {
        return ((long long) shop << 20) | movie;
    }
};
