		Tema 1 EGC
Vlaescu Adrian-Cristian
336CA

		Flappy Bird
	Implementarea temei porneste de la scheletul pentru laboratorul 3.
In Object2D.cpp am implementat cateva functii ce imi creaza diferite corpuri 
geometrice cum ar fi: un dreptunghi, pasarea, fundalul, o zona de pamant unde
sunt asezate dreptunghiurile de jos.
	Pentru scalarea dreptunghiurilor, am declarat 2 vectori, unul care
micsoreaza obiectele, altul care le mareste. Am creat un obiect pentru
dreptunghiurile de jos si unul pentru cele de sus, un obiect pentru backround,
un obiect pentru floor si unul pentru pasare.
	In OnKeyPress verific daca se apasa tasta SPACE, caz in care o
variabila booleana isi schimba valoare. Totusi am adaugat o functionalitate in
plus, aceea ca jocul nu va incepe pana cand nu se apasa SPACE, o simulare a 
startului.
	In Update, verific daca pressSpace este false, caz in care translateY
va scadea, astfel pasarea va parea ca o sa cada, la un anumit unghi, iar daca
pressSpace este true, pasarea va sari o anumita distanta in sus, o distanta
fata de pozitia ei curenta, la un anumit unghi. In caz ca jocul s-a terminat,
adica gameOver este true, translatez pasarea pe podea, astept 100 de frameuri
si afisez punctajul si jocul se termina. Acel if care verifica daca counter
este multiplu de 5 este pentru a face saltul pasarii mai fluid, adica 5 frame-
uri de la apasarea tastei SPACE, pasarea sa sara, astfel incat sa nu fie
trecerea atat de rapida intre angularStepOY pozitiv si unul negativ.
Pentru pasarea am calculat un punct central pentru pozitionarea in coordonatele
xOy, iar pentru miscarea ei am facut urmatorul calcul pentru matricea de modelare
M = T(P) * R(theta) * T(-P) * T(0,translateY).
La fiecare 3 din 4*deltaTimeSeconds se genereaza un nou dreptunghi jos is unul nou sus.
Dreptunghiurile initiale le translatez cu translateX si apoi intru intr-o bucla
for in care initial calculez pozitia fiecarui dreptunghi pe OX, scalez
dreptughiurile in functie de indicele dreptunghiului, iar pentru fiecare dreptunghi
in parte inmultesc matricea curenta de la pasul i cu Scale(vectorScaleDown/Upper[i]),
apoi o translatez fata de vecinul din stanga cu o distanta aleasa de mine.
Pentru dreptunghiurile de sus, am aplicat acelasi algoritm ca si cel aplicat 
pasarii, adica M *= T(P) * S(number) * T(-P) * T(distanceBetweenRectangles), unde
P este coltul din stanga sus al ecranului, un fel de origine pentru 
dreptunghiurile de sus, cum punctul (0,0) este o origine pentru dreptunghiurile
de jos. Am dat RenderMesh2D doar la dreptunghiurile care la momentul respectiv
se pot vedea pe ecran.
	Pentru coliziuni, am incadrat pasarea intr-un dreptunghi si am verificat
pentru partea de jos, ca Y-ul celor doua puncte ale pasarii sa fie mai mic
ca Y-ul dreptunghiului curent si ca leftDownCorner.x sau rightDownCorner.x
sa fie in intervalul (coltul sus stanga al dreptunghiului,coltul sus drepata al dreptunghiului).
Asemanator este si pentru ciocnirile cu dreptunghiurile de sus.
	diffDown si diffUp sunt inaltimile dreptunghiurilor de jos si de sus
la pasul i. Scalarea dreptunghiurilor am facut-o in functie de cel mai apropiat
dreptunghi din stanga al celui curent.

!!!!Plecand ca schelet de la laboratorul 3, am implementat tema in folderul Laborator3
din folderul Laboratoare
