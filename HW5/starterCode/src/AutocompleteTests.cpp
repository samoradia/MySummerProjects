#include "AutocompleteTests.h"
#include "Autocomplete.h"
using namespace std;
ENABLE_TESTS();

ADD_TEST("Check simple one-letter prefix searches.") {
    Set<string> toInsert = {
        "Fork",
        "Knife",
        "Spoon",
        "Silverware"
    };

    /* Add all the words to the Autocomplete structure. */
    Autocomplete ac;
    for (auto word: toInsert) {
        ac.add(word);
    }

    /* Query for just the "K" words. */
    auto result = ac.suggestionsFor("K", 137);
    expect(result.size() == 1);
    expect(result.first() == "Knife");

    /* Query for words starting with "S". */
    result = ac.suggestionsFor("S", 137);
    expect(result.size() == 2);
    expect(result.contains("Spoon"));
    expect(result.contains("Silverware"));

    /* Query for (nonexistent) words starting with "Q". */
    expect(ac.suggestionsFor("Q", 137).isEmpty());
}

ADD_TEST("Check searches with an empty prefix.") {
    Set<string> toInsert = {
        "Dikdik",
        "Quokka",
        "Sloth",
        "Nubian Ibex"
    };

    /* Add all the words to the Autocomplete structure. */
    Autocomplete ac;
    for (auto word: toInsert) {
        ac.add(word);
    }

    /* Querying with an empty prefix should return all the words, assuming
     * we don't cut off the search early.
     */
    expect(ac.suggestionsFor("", toInsert.size()) == toInsert);
}

ADD_TEST("Check for searches with a 0 size limit.") {
    Set<string> toInsert = {
        "Dikdik",
        "Quokka",
        "Sloth",
        "Nubian Ibex"
    };

    /* Add all the words to the Autocomplete structure. */
    Autocomplete ac;
    for (auto word: toInsert) {
        ac.add(word);
    }

    /* Querying with an empty prefix should return all the words, assuming
     * we don't cut off the search early.
     */
    expect(ac.suggestionsFor("Dikdik", 0).isEmpty());
    expect(ac.suggestionsFor("Qu", 0).isEmpty());
    expect(ac.suggestionsFor("X", 0).isEmpty());
}

ADD_TEST("Check for searches stopped by size limit.") {
    /* Thanks, Wikipedia's "List of English Prepositions!" */
    Set<string> toInsert = {
        "Aboard",   "About",    "Above",    "Absent",    "Across",
        "After",    "Against",  "Along",    "Alongside", "Amid",
        "Among",    "Apropos",  "Apud",     "Around",    "As",
        "Astride",  "At",       "Atop",
    };

    /* Add all the words to the Autocomplete structure. */
    Autocomplete ac;
    for (auto word: toInsert) {
        ac.add(word);
    }

    /* Query for up to five things starting with A. We should get five distinct values
     * that are all elements of toInsert.
     */
    auto elems = ac.suggestionsFor("A", 5);
    expect(elems.size() == 5);
    expect(toInsert.containsAll(elems));
}

ADD_TEST("Searches shouldn't fail if there aren't enough items to go around.") {
    /* Thanks, Wikipedia's "List of English Prepositions!" */
    Set<string> toInsert = {
        "Aboard",   "About",    "Above",    "Absent",    "Across",
        "After",    "Against",  "Along",    "Alongside", "Amid",
        "Among",    "Apropos",  "Apud",     "Around",    "As",
        "Astride",  "At",       "Atop",
    };

    /* Add all the words to the Autocomplete structure. */
    Autocomplete ac;
    for (auto word: toInsert) {
        ac.add(word);
    }

    /* If we query for 100,000 elements, we should get everything back. */
    expect(ac.suggestionsFor("A", 100000) == toInsert);
}

ADD_TEST("Search adds words that have the same prefix as another word in the list"){
    Set<string> toInsert = {
        "Bat", "Batty"
    };
    Autocomplete autocomp;
    for (auto word: toInsert){
        autocomp.add(word);
    }


    //both bat and batty should appear in a search for B, with excess space
     auto elems = autocomp.suggestionsFor("B", 5);
    expect(elems.size() == 2);
    expect(elems == toInsert);
}
ADD_TEST("If initial prefix is a valid title, it is added to the Set"){
    Set<string> toInsert = {
        "Will"
    };
    Autocomplete autocomp;
    for (auto word: toInsert){
        autocomp.add(word);
    }


     //Will should be found in the set
     auto elems = autocomp.suggestionsFor("Will", 5);
     expect(elems.size() == 1);
     expect(elems == toInsert);

}
/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */
