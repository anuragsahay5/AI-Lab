%  Find last element of a list
last_element([H],H).
last_element([H|T],X):-
    last_element(T,X).


%  Append two lists
append_lists([],L,L).
append_lists([H|L1],L2,[H|L]):-
    append_lists(L1,L2,L).


%  Reverse a list
reverse_list([],[]).
reverse_list([H|T],L):-
    reverse_list(T,L1),
    append_lists(L1,[H],L).
    

% Check if list is palindrome
isPalindrome(L):-
    reverse_list(L,L).


element_at(X,[X|Xs],0).
element_at(X,[_|Xs],N):-
    N1 is N-1,
    element_at(X,Xs,N1).


find_average([],0,0).
find_average(L,S,A):-
sum_list(L,Sum),
length(L,Len),
S is Sum,
A is Sum / Len.


gcd(A,0,A).
gcd(0,B,B).
gcd(X,X,X).
gcd(A,B,G):-
    A>B, X is A-B, gcd(X,B,G).
gcd(A,B,G):-
    A<B, X is B-A, gcd(A,X,G).



solve(N,X):-
    X >= N -> true;
    0 is N mod X -> false;
    T is X + 1,
    solve(N,T).

is_prime(N):-
    solve(N,2).


prime_factor_solve(N,F,[F|T]):-
    0 is N mod F,
    N1 is N // F,
    prime_factor_solve(N1,F,T).

prime_factor_solve(N,F,[N|T]):-
    F * F > N,
    N > 2.

prime_factor_solve(N,F,L):-
    F * F < N,
    N mod F =\= 0,
    T is F + 1,
    prime_factor_solve(N,T,L).

prime_factor(2,[2]).
prime_factor(4,[2,2]).
prime_factor(N,L):-
    N > 1,
    prime_factor_solve(N,2,L).



goldbach(N,A,B):-
    T is N // 2 - 1,
    between(2, T, A),
    is_prime(A),
    B is N - A,
    is_prime(B).


fibonacci(1,0).
fibonacci(2,1).
fibonacci(N,A):-
    T1 is N-1,
    T2 is N-2,
    fibonacci(T1,R1),
    fibonacci(T2,R2),
    A is R1 + R2.

fib_solve(1).
fib_solve(N):-
    T is N - 1,
    fib_solve(T),
    fibonacci(T,R),
    write(R),write(' ').

fib(N):-
    T is N + 1,
    fib_solve(T).


% 12. a
parent(john,ann).
parent(jim,john).
parent(jim,keith).
parent(mary,ann).
parent(mary,sylvia).
parent(brian,sylvia).

male(keith).
male(jim).
male(brian).
female(sylvia).
female(ann).

grandparent(X,Y):-
    parent(X,Z),
    parent(Z,Y).

uncle(X,Y):-
    parent(Z,X),
    grandparent(V,Y),
    Z == V.

%  12. b
halfsister(X,Y):-
    parent(A,X),
    parent(B,X),
    parent(A,Y),
    parent(C,Y),
    female(X),
    female(Y),
    not(A = B),
    not(A = C),
    not(B = C).

% Assignment - 2


% 1. To duplicate the elements of a list, a given number of times.
duplicate(_, 0, []).
duplicate(List, N, DuplicatedList) :-
    N > 0,
    duplicate_helper(List, N, DuplicatedList).

duplicate_helper([], _, []).
duplicate_helper([Elem|Tail], N, DuplicatedList) :-
    duplicate_element(Elem, N, DuplicatedElem),
    duplicate_helper(Tail, N, RestDuplicatedList),
    append(DuplicatedElem, RestDuplicatedList, DuplicatedList).

duplicate_element(_, 0, []).
duplicate_element(Element, N, [Element|RestDuplicatedElem]) :-
    N > 0,
    N1 is N - 1,
    duplicate_element(Element, N1, RestDuplicatedElem).


% 2) To determine whether a list is a sub list of another list. 
% if T is the prefix of R?
prefix([], _).
prefix([Elem|Tail], [Elem|Rest]) :-
    prefix(Tail, Rest).

sublist([], _).
sublist([X|L], [X|R]) :- 
    prefix(L, R).
sublist(L, [_|R]) :- 
    sublist(L, R).

% checks if L is a sublist of R

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
split(L, 0, [], L).
split([Elem|Tail], N, [Elem|FirstPart], SecondPart) :-
    N1 is N - 1,
    split(Tail, N1, FirstPart, SecondPart).


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
pack([X], [[X]]).
pack([X, X|T], [[X|Xs]|Rest]) :-
    pack([X|T], [Xs|Rest]).
pack([X, Y|T], [[X]|Rest]) :-
    X \= Y,
    pack([Y|T], Rest).

encode([], []).
encode([X], [[1, X]]).
encode([X, X|T], [[N, X]|Rest]) :-
    encode([X|T], [[M, X]|Rest]),
    N is M + 1.
encode([X, Y|T], [[1, X]|Rest]) :-
    X \= Y,
    encode([Y|T], Rest).

% 10) smoothies
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