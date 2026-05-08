#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Costanti constexpr per standard C++ moderno
constexpr int MAX_PRODOTTI = 100;
const string NOME_FILE = "magazzino_dati.txt";

struct Prodotto {
    string nome = "";
    int quantita = 0;
    float prezzo = 0.0;
};

// --- PROTOTIPI ---
int mostraMenu();
void caricaDaFile(Prodotto inventario[], int &n);
void salvaSuFile(const Prodotto inventario[], int n);
void aggiungiProdotto(Prodotto inventario[], int &n);
void visualizzaInventario(const Prodotto inventario[], int n);
void leggiFileDirettamente(); // La funzione che mancava!

// --- MAIN ---
int main() {
    Prodotto inventario[MAX_PRODOTTI];
    int numeroProdotti = 0;
    int scelta;

    // Carichiamo i dati esistenti all'avvio
    caricaDaFile(inventario, numeroProdotti);

    do {
        scelta = mostraMenu();

        switch (scelta) {
            case 1:
                visualizzaInventario(inventario, numeroProdotti);
                break;
            case 2:
                aggiungiProdotto(inventario, numeroProdotti);
                break;
            case 3:
                salvaSuFile(inventario, numeroProdotti);
                break;
            case 4:
                leggiFileDirettamente();
                break;
            case 0:
                cout << "Uscita in corso..." << endl;
                break;
            default:
                cout << "Scelta non valida!" << endl;
        }
    } while (scelta != 0);

    return 0;
}

// --- DEFINIZIONI ---

int mostraMenu() {
    int opz;
    cout << "\n=== GESTIONALE PRODOTTI v2.0 ===" << endl;
    cout << "1. Mostra Array (RAM)" << endl;
    cout << "2. Aggiungi Prodotto (RAM)" << endl;
    cout << "3. Salva Array su File (Scrittura)" << endl;
    cout << "4. Leggi File Direttamente (Senza RAM)" << endl;
    cout << "0. Esci" << endl;
    cout << "Scelta: ";
    if (!(cin >> opz)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    cin.ignore(); // Pulisce il buffer per la prossima getline
    return opz;
}

/**
 * Legge il file e popola l'array di struct (RAM).
 */
void caricaDaFile(Prodotto inventario[], int &n) {
    ifstream fin(NOME_FILE);
    if (!fin) return;

    n = 0;
    string tempNome;
    while (n < MAX_PRODOTTI && getline(fin, tempNome)) {
        inventario[n].nome = tempNome;
        fin >> inventario[n].quantita;
        fin >> inventario[n].prezzo;
        fin.ignore(); // Salta il \n dopo il prezzo
        n++;
    }
    fin.close();
    cout << "[INFO] " << n << " record caricati in RAM." << endl;
}

/**
 * Funzione che legge il file e lo stampa direttamente.
 * Utile per verificare cosa c'e' sul disco senza modificare l'array.
 */
void leggiFileDirettamente() {
    ifstream fin(NOME_FILE);
    if (!fin) {
        cout << "[ERRORE] File non trovato." << endl;
        return;
    }

    string nome;
    int qta;
    float pr;

    cout << "\n--- CONTENUTO DIRETTO DEL FILE ---" << endl;
    while (getline(fin, nome)) {
        fin >> qta;
        fin >> pr;
        fin.ignore(); // Importante per la prossima getline
        cout << "Prodotto: " << nome << " | Qta: " << qta << " | Prezzo: " << pr << endl;
    }
    fin.close();
}

void salvaSuFile(const Prodotto inventario[], int n) {
    ofstream fout(NOME_FILE);
    if (!fout) return;

    for (int i = 0; i < n; i++) {
        fout << inventario[i].nome << endl;
        fout << inventario[i].quantita << endl;
        fout << inventario[i].prezzo << endl;
    }
    fout.close();
    cout << "[OK] Salvataggio completato." << endl;
}

void aggiungiProdotto(Prodotto inventario[], int &n) {
    if (n >= MAX_PRODOTTI) {
        cout << "[ERRORE] Array pieno." << endl;
        return;
    }

    cout << "Inserisci nome: ";
    getline(cin, inventario[n].nome);
    cout << "Quantita': ";
    cin >> inventario[n].quantita;
    cout << "Prezzo: ";
    cin >> inventario[n].prezzo;
    cin.ignore();

    n++;
    cout << "[OK] Prodotto aggiunto." << endl;
}

void visualizzaInventario(const Prodotto inventario[], int n) {
    if (n == 0) {
        cout << "RAM vuota. Carica dati o inserisci prodotti." << endl;
        return;
    }
    cout << "\n--- DATI IN MEMORIA RAM ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ") " << inventario[i].nome << " [" << inventario[i].quantita << " pz]" << endl;
    }
}