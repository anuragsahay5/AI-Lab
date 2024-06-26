% 1. To duplicate the elements of a list, a given number of times.
duplicate(_, 0, []).
duplicate(List, N, DuplicatedList) :-
    N > 0,
    duplicateHelper(List, N, DuplicatedList).

duplicateHelper([], _, []).
duplicateHelper([H|T], N, DuplicatedList) :-
    duplicateElement(H, N, DuplicatedElement),
    duplicateHelper(T, N, RestDuplicatedList),
    append(DuplicatedElement, RestDuplicatedList, DuplicatedList).

duplicateElement(_, 0, []).
duplicateElement(Element, N, [Element|RestDuplicatedElement]) :-
    N > 0,
    N1 is N - 1,
    duplicateElement(Element, N1, RestDuplicatedElement).

% 2) To determine whether a list is a sub list of another list. 
% if T is the prefix of R?
prefix([], _).
prefix([X|T], [X|R]) :- prefix(T, R).
% if T is the sublist of R?
sublist([], _).
sublist([X|T], [X|R]) :- prefix(T, R), !.
sublist(L, [_|R]) :- sublist(L, R).

% 3) To determine intersection, union, difference, symmetric difference of two sets.
intersection([], L, []).
intersection([X|Xs], L, [X|Tail]) :-
    member(X, L),
    intersection(Xs, L, Tail).
intersection([X|Xs], L, L1) :-
    \+ member(X, L),
    intersection(Xs, L, L1).


union([], Set2, Set2).
union([H|T1], Set2, [H|Tail]) :-
    \+ member(H, Set2),
    union(T1, Set2, Tail).
% If H is already a member of Set2, skip it and continue with the rest.
union([H|T1], Set2, Union) :-
    member(H, Set2),
    union(T1, Set2, Union).

difference([], L, []).
difference([X|Xs], L, [X|Tail]) :-
    \+ member(X, L),
    difference(Xs, L, Tail).
difference([X|Xs], L, [Tail]) :-
    member(X, L),
    difference(Xs, L, Tail).

% 4) Transpose L1, L2 into L. That is, if L1 = [a, b, c] and L2 = [1, 2, 3], then L = [(a, 1), (b,2), (c, 3)]
transpose([], [], []).
transpose([X|Xs], [Y|Ys], [(X, Y)|T]) :-
    transpose(Xs, Ys, T).

% 5) To split a list into two parts; the length of the first part is given.
split(L, 0, L1, L).
split([X|Xs], N, [X|Xss], L2) :-
    N1 is N - 1,
    split(Xs, N1, Xss, L2).

% 6) To extract a slice from a list. slice([a, b, c, d, e, f, g, h, i, j, k], 3, 7, L).
% slice(_, End, End, []).
slice(X, A, B, C) :- 
    A1 is A - 1,
    slice_helper(X, A1, B, C).
slice_helper(X, 0, 0, L).
slice_helper([_|T], Start, End, Slice) :-
    NextEnd is End - 1,
    NextStart is Start - 1,
    slice_helper(T, NextStart, NextEnd, Slice).
slice_helper([H|T], 0, End, [H|Slice]) :-
    NextEnd is End - 1,
    slice_helper(T, 0, NextEnd, Slice).

% 7) combinations(3, [a, b, c, d, e, f], L).L = [a, b, c]; L = [a, b, d]; L = [a, b, e];
combinations(0, _, []).
combinations(N, [X|Xs], [X|Ys]) :- 
    N1 is N-1, 
    combinations(N1, Xs, Ys).
combinations(N, [_|Xs], Y) :- 
    N > 0, 
    combinations(N, Xs, Y).

% 9) Pack and Encode
pack([], []).
pack([Elem], [[Elem]]).
pack([Elem, Elem|Tail], [[Elem|Xs]|Rest]) :-
    pack([Elem|Tail], [Xs|Rest]).
pack([X, Y|T], [[X]|Rest]) :-
    X \= Y,
    pack([Y|T], Rest).

encode([], []).
encode([Elem], [[1, Elem]]).
encode([Elem, Elem|T], [[N, Elem]|Rest]) :-
    encode([Elem|T], [[M, Elem]|Rest]),
    N is M + 1.
encode([X, Y|T], [[1, X]|Rest]) :-
    X \= Y,
    encode([Y|T], Rest).

% 10) some bullshit about smoothies
store(best_smoothies, 
    [alan,john,mary],
    [smoothie(berry, [orange, blueberry, strawberry], 2),
    smoothie(tropical, [orange, banana, mango, guava], 3),
    smoothie(blue, [banana, blueberry], 3) ]).

store(all_smoothies, 
    [keith,mary],
    [smoothie(pinacolada, [orange, pineapple, coconut], 2),
    smoothie(green, [orange, banana, kiwi], 5),
    smoothie(purple, [orange, blueberry, strawberry], 2),
    smoothie(smooth, [orange, banana, mango],1) ]).

store(smoothies_galore, 
    [heath,john,michelle],
    [smoothie(combo1, [strawberry, orange, banana], 2),
    smoothie(combo2, [banana, orange], 5),
    smoothie(combo3, [orange, peach, banana], 2),
    smoothie(combo4, [guava, mango, papaya, orange],1),
    smoothie(combo5, [grapefruit, banana, pear],1) ]).

% a) 
more_than_four(A) :-
    store(A, _, B),
    length(B, Length),
    Length >= 4,
    true.

% b) 
exists(A) :-
    store(_, _, B),
    member(smoothie(A, _, _), B).

% c) 
ratio(A, R) :-
    store(A, B, C),
    length(B, X),
    length(C, Y),
    R is X / Y.

% d) 

average(A, X) :-
    store(A, _, C),
    average_helper(C, Y),
    length(C, Z),
    X is Y / Z.

average_helper([], 0).
average_helper([smoothie(_, _, Price)|Rest], Total) :-
    average_helper(Rest, RestTotal),
    Total is RestTotal + Price.

% e) 
smoothies_in_store(A, X) :-
    store(A, _, C),
    extractSmoothieNames(C, X).

extractSmoothieNames([], []).
extractSmoothieNames([smoothie(Name, _, _)|Rest], [Name|RestSmoothieNames]) :-
    extractSmoothieNames(Rest, RestSmoothieNames).

% f) 
fruit_in_all_smoothies(Store, Fruit) :-
    store(Store, _, Smoothies),
    check_all_smoothies(Smoothies, Fruit).

check_all_smoothies([], _).
check_all_smoothies([smoothie(_, Ingredients, _)|Rest], Fruit) :-
    member(Fruit, Ingredients),
    check_all_smoothies(Rest, Fruit).
