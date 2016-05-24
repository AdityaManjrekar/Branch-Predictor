# Branch-Predictor
A	progra
m	containing	
ten
branches	was	executed,	and	a	trace	was	captured	of	the
dynamic
instruction	sequence.		
A
ll
no
n
-
branch	instructions	have	been	removed,	and	branch	addresses	have	
been	renumbered	from	0	to	9.
This	trace
of	10000	branches
is	provided	in
“
sampl
e_
branch_sequence.txt”.		
(
There	is	a	program	of	10	branches,	and	the	
sample	input	
file	is	a	
sequence	of	10000	executions	of
those	branches
.
)
Your	task	is	to	write	a	
tournament	
branch	predictor
that	attempts	to	predict	these	branches.
The	tournament	branch	predictor	is	described	in	the	class	notes
on	pages	258
a
nd	259
,	and	a	
diagram	is	provided	below.		
You	are	also	encouraged
to	read	the	Wikipedia	article	at	
http://en.wiki
pedia.org/wiki/Branch_prediction
,	where	this	is	referred	to	as	a	“Hybrid	predictor.”
Two
-
bit	saturating	cou
nters	are	described	on	pages	238
to	240
.		To	understand	g
lobal	predictors,	
read	pages	248	to	254
,	and	consider	the	case	where	
