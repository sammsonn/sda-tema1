**Nume: SAMSON Alexandru-Valentin**
**Grupă: 312CC**


## Tema 1 – Liste dublu inlănțuite, stive și cozi


### Descriere:

* Acesta este un program ce implementează o bandă magică capabilă să primească
și să execute comenzi. Programul folosește o listă dublu înlănțuită pentru a
reprezenta banda, o stivă pentru a memora nodurile parcurse și o coadă pentru
a stoca operațiile care trebuie efectuate pe bandă.

* Programul folosește mai multe structuri pentru a reprezenta diferitele
componente. O structură listNode reprezintă un nod din lista dublu înlănțuită,
care conține un caracter și pointeri către nodurile următoare și precedente.

* O structură de bandă reprezintă banda, care conține indicatori către nodul
santinelă (care reprezintă începutul benzii) și nodul deget (care reprezintă
poziția curentă pe bandă).

* O structură queueCell reprezintă o celulă din coadă, care conține un șir
reprezentând operația care trebuie efectuată pe bandă. O structură de coadă
conține indicatori către partea din față și din spate a cozii.

* O structură stackCell reprezintă o celulă din stivă, care conține un
indicator către poziția de pe bandă și un indicator către următoarea celulă
din stivă.

* Programul conține mai multe funcții pentru inițializarea și manipularea
acestor structuri. Funcția initList inițializează nodul santinelă al listei
duble înlănțuite, precum și primul nod propriu-zis. Funcția addList adaugă un
nou nod la listă. Funcția initStack inițializează o stivă goală. Funcția
pushStack adaugă un nou element la stivă. Funcția popStack elimină elementul
din vârful stivei. Funcția initQueue inițializează o coadă goală. Funcția
addQueue adaugă o nouă celulă la coadă. Funcția delQueue elimină prima celulă
din coadă.

* Funcția main a programului citește un fișier care conține datele de intrare,
inițializează banda, stiva și coada și efectuează operațiile specificate în
fișier, care se împart în mai multe categorii:

## Operații de tip UPDATE: "MOVE_LEFT", "MOVE_RIGHT", "MOVE_LEFT_CHAR <C>",
## "MOVE_RIGHT_CHAR <C>", WRITE <C>, INSERT_LEFT <C> și INSERT_RIGHT <C>

## Operații de tip QUERY: "SHOW_CURRENT", "SHOW"

## Operații de tip UNDO / REDO

## Operația EXECUTE

* După efectuarea operațiilor, programul afișează starea finală a benzii.
În final, acesta eliberează memoria alocată pentru bandă, stivă și coadă.


### Comentarii asupra temei:

* Implementarea mi se pare destul de bună, am reușit să nu am leak-uri de
memorie, dar sigur era posibil să fie și mai eficientă sau mai scurtă. Totuși
sunt mulțumit cu această rezolvare.

* Tema această m-a învățat cum să lucrez cu liste, stive și cozi, și cum să
folosesc cât mai eficient memoria.

### Punctajul obținut la teste local:

* Total: 100.0/100
* Valgrind: 20/20