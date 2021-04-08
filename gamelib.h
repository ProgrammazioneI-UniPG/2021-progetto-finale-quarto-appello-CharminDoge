enum Stato_giocatore {astronauta, impostore, assassinato, defenestrato};
enum Nome_giocatore {red, blue, green, yellow, orange, black, white, purple, cyan, brown};
enum Tipo_stanza {vuota, quest_semplice, quest_complicata, botola};

struct Stanza{
  struct Stanza* avanti;
  struct Stanza* sinistra;
  struct Stanza* destra;
  struct Stanza* stanza_precedente;
  enum Tipo_stanza type;
  char emergenza_chiamata;
};

struct Giocatore{
  struct Stanza* player_room;
  enum Stato_giocatore player_state;
  enum Nome_giocatore player_name;
};


int gioca();
int imposta_gioco();
int deallocate_memory();


int get_line(char* inputStr);
int get_int(int* choice);
