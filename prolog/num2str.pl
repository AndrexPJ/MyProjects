
numToStr(0,'zero').
numToStr(1,'one').
numToStr(2,'two').
numToStr(3,'three').
numToStr(4,'four').
numToStr(5,'five').
numToStr(6,'six').
numToStr(7,'zero').
numToStr(8,'eight').
numToStr(9,'nine').
numToStr(_,'!'):-!.
getNum(X,0):- numToStr(X,Z),write(Z),!.
getNum(X,_):- numToStr(X,Z), Z\='!'  ->write(Z), write('-'),!;!.

nStr([]):-!.
nStr([H|T]):-length(T,L),Z is H - 48,getNum(Z,L),nStr(T).

num2str(X):- integer(X),number_codes(X,S),nStr(S).



parseInt(X,A):-parseInt2(X,A,[]).

mod2(X,Y,Z) :- X > Y -> Z is X mod Y ; Z is 0. 

parseInt2(0,A,B):- A = B,!.
parseInt2(X,A,B):-X < 10 -> A = [X|B]; (mod2(X,10,M),X2 is (X-M)/10,X3 is round(X2),parseInt2(X3,A,[M|B])).
