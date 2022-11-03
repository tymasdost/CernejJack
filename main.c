#include <stdio.h> //
#include <math.h>  // Importace balicku
#include <time.h>  //

// for (int i = 0; i < 52; i++) printf("%d ", deck[i]); | Slouzilo pro vypisovani hraciho balicku :)

int cardReadValue(int cardID) // Funkce pro precteni hodnoty karty
{
    int value; // promena pro vraceni hodnoty karty

    switch (cardID % 13) // tady se to vlastne jakoby vypocita
    {
    case 0:
        value = 11; // kdyz je karta jakoby A tak se ji da hodnota 11
        break;
    case 10:
        value = 10; // kdyz je karta jakoby J tak se ji da hodnota 10
        break;
    case 11:
        value = 10; // kdyz je karta jakoby Q tak se ji da hodnota 10
        break;
    case 12:
        value = 10; // kdyz je karta jakoby K tak se ji da hodnota 10
        break;
    default:
        value = (cardID % 13) + 1; // kdyz je karta jina nez ty ostatni tak zbytek po deleni poctem karet se stejnym symbolem tak to vyjde takle protoze sem si to takle udelal aby to nebylo tak slozity.
    }

    return value; // tady se to vrati
}

void createDeck(int *deck) // tady vlastne vytvarim balicek s kartama na zacatku hry a kdyz dojdou karty
{
    int newDeck[52] = {0}; // tady si udelam krabicku na ty karticky
    for (int i = 1; i <= 52; i++)
        deck[i - 1] = i; // tady se to zalamuje nejak divne ale vlastne to je k tomu aby se do toho pole postupne ulozily hodnoty od 1 do poctu karet nebo-li 52 jelikoz 13 * 4 je 52 :P
}

void shuffleDeck(int *deck) // tady ten balicek prohazim aby to neslo postupne
{
    time_t t;                    // tady sem si musel udelat promenou nevim co dela to sem si nasel jinak by to dole svitilo :-)
    int new, temp;               // tady si delam pomocne promene pro prehazeni prvku v poly
    int rand(void);              // tohle je definice pro ten random generator btw
    srand((unsigned)time(&t));   // a kdyz tady nebude tenhle radek tak ten generator bude davat porad stejnou posloupnost tech cisel ze se jako pri znovuspusteni programu nezmeni
    for (int i = 0; i < 52; i++) // tady uz se nam to micha
    {
        new = rand() % 52;   // tohle hodi random cisilko od 0 do 51
        temp = deck[i];      // tady se ulozi prvek kterej se bude menit
        deck[i] = deck[new]; // tady se ulozi do toho meniciho se ten co se nahodne vybral
        deck[new] = temp;    // tady se do toho co se nahodne vybral ulozi zas ten co se zmenil nahore chapem se ne? :)
    }
    for (int i = 0; i < 52; i++)
        printf("%d ", cardReadValue(deck[i]));
}

void throwCard(int *deck, int size) // tady to sebere prvni prvek v tom poly kdyz se jako zahraje ta karta tak aby tam nebyla
{
    for (int i = 0; i < size; i++) // tady se to pole musi projet cely protoze tady na to neni zadna metoda tak se to musi udelat takhle slozite / no mozna to mohlo bejt slozitejsi ale je to jakoby narocny na tu vypocetni techniku kdyz se to musi cely projet a posnutou
    {
        deck[i] = deck[i + 1]; // tady se nahrazuje soucasnej prvek tim co je vedle nej takze ten prvni se vysune vlastne jako pryc
    }
    size--; // a pak se tady odebere velikost toho pole o 1
}

char askForCard() // tady se to pta gemblera jestli si veme dalsi kartu
{
    printf("\nDo you want to take next card? (y/n)"); // tady se ho to jako zepta
    char temp_ans;                                    // tady je promena na tu jeho odpoved
    int inputCheck = scanf("%s", &temp_ans);          // tady se naskenuje a mam tady kontrolu kdyby tam dal cislo blazen
    while (inputCheck == 0)                           // tady while kdyz to zada spatne tak mu to bude spamovat do nekonecna dokud to neda aby prisel o penize $$$$
    {
        while (getchar() != '\n')            // tady se musi vyprazdnit zasobnik pro jistotu
            ;                                // formatovani vsccka na houby uplne
        printf("Bad input try again\n");     // tady ho to upozorni
        inputCheck = scanf("%d", &temp_ans); // tady to zas naskenuje odpoved uzivatele
    }
    return temp_ans; // vrati to promenou zpatky do mainu
}

int main() // main funkce / funkce zivota / tady to je jakoby jadro tohohle programu
{

    printf("       | Welcome to CASINO ROYAL |\n");            // uvitaci slogan
    printf("| You will earn 5000 as a welcome bonus |\n\n\n"); // tady to nahodi nejak cash do zacatku
    int funds = 5000;                                          // presneji tady se to tam ulozi
    int size = 52;                                             // velikost pole vyuzivana tam nahore u toho mazani
    int deck[size];                                            // tady se udela to pole na karty
    createDeck(deck);                                          // zavola se funkce ta nahore jak to vytvarelo ten balik a posle to tam i to pole jakoby ten balik s kartama
    shuffleDeck(deck);                                         // zavola se funkce ta nahore jak to michalo ten balik a posle to tam i to pole jakoby ten balik s kartama
    while (funds >= 10)                                        // tady je loop na celej ten program aby se nevypnul kdyz se jednou dokonci ale kdyz taky bude ten gembler jakoby min jak 10$ tak se ukonci a hodi mu to peknou hlasku
    {
        if (size < 10) // kdyz velikost toho balicku je min jak 10 tak se provede ta podminka
        {
            int size = 52;     // velikost se da zpatky na 52
            createDeck(deck);  // vytvori se znova balicek s kartama
            shuffleDeck(deck); // a zamicha se taky ten balicek znovu
        }
        printf("\n\nHow much you want to bet? (10 - %d)\n", funds); // tady se vypise kolik chce vsadit a to tam pak napise no a jeste mu to tam da kolik muze vsadit max a to je ten jeho financni obnos zase

        int inputCheck = 0; // tady je promena na kontrolu toho vstupu
        int bet;            // promena na ulozeni sazky uzivatele/uzivatelky

        inputCheck = scanf("%d", &bet);                    // tady nascenuje zadana sazka
        while (inputCheck == 0 || bet < 10 || bet > funds) // tady je zas takzvane smycka while a ta se bude opakovat dokud nezada spravne hodnoty na tu sazku co dava
        {
            while (getchar() != '\n')                                           // vycisteni bufferu myslim
                ;                                                               // zarovnavani na prkenou ohradu zjednodusene
            printf("Bad input please enter your bet again (10 - %d)\n", funds); // tady to napise ze neumi cist a zadal blbost
            inputCheck = scanf("%d", &bet);                                     // nacte se hodnota znova
        }

        int playerCards = 0,                    // promena na velikost tech karet co ma hrac
            dealerCards = 0,                    // promena na velikost tech karet co ma hrac
            pbj = 0,                            // tady se dela promena na to kdyby uzivatelovovy padl blackjack jelikoz jsem to delal uplne na konec tyhle veci tak sem to udelal takhle jak vandrak
            dbj = 0,                            // tady se dela promena na to kdyby dealerovy padl blackjack jelikoz jsem to delal uplne na konec tyhle veci tak sem to udelal takhle jak vandrak
            pace = 0,                           // to je pocet es jakoby ESO (A) 11/1 aby se to mohlo odecist kdyz bude mit pres 21
            dace = 0,                           // to je pocet es jakoby ESO (A) 11/1 aby se to mohlo odecist kdyz bude mit pres 21 no to je to stejny akorat pro dealera a ne pro usera
            firstCard = cardReadValue(deck[0]); // tady to veme kartu pro dealera mimo aby se neukazovala a byla neznama dokud hrac prestane brat karty
        throwCard(deck, size);                  // tady se odebera ta 1 karta z baliku

        printf("\n|| Game Starting ||\n\n"); // upozorneni ze hra zacala ale davno probiha takze to je takzvane falesna informace
        for (int i = 0; i <= 2; i++)         // tady to da vsem 2 karty nize si vysvtlime prodobneji D:
        {
            int value = cardReadValue(deck[0]); // nacte se hodnota prvni karty v hromadce
            if (i == 0)                         // tady sem to rozradil aby se 1 dala dealerovy a zbytek hracovi sice to ma byt na prsekacku a stacilo by zmenit jen podminku ale nechce si mi to delat momentalne mozna to predelam ale zapomenu na tenhle dlouhej komentar a neprepisu ho takze tohle tady zustane a timto zdravim sve budouci ja az to budu ukazovat ve skole
            {
                dealerCards += value; // tady se ta karta pricte k dealerovy do balicku nebo na ruku to je asi jedno
                if (value == 11)      // zase se to zarovnalo uplne na nic takze to dela to kdyz je to eso tak se to ulozi do promeny abych s tim pak mohl dale pracovat
                    dace++;           // tady se to pricte no
            }
            else // a kdyz to neni ten dealer tak to udela to sami ale u hrace
            {
                playerCards += value; // tady se pricte ta hodnota
                if (value == 11)      // tady se zas kontroluje to jestli to neni eso
                    pace++;           // inkrementace promene pace | playerACES zkracene
            }

            throwCard(deck, size); // tady to zahodi kartu kdyz uz neni potreba proste je smazu zivot
        }
        if (dealerCards + firstCard == 21)                                                       // kontrola blackjacku u dealera kdyz ty jeho 2 karty sou dohromady 21 tak jinak nez 10 a esem to nejde
            dbj = 1;                                                                             // tady se to hodi aby se to mohlo dole uknockit pak tam sou podminky diky kterejm se ten kod nebude zbytecne provaded :3
        if (playerCards == 21)                                                                   // tady se to taky kontroluje znovu u hrace
            pbj = 1;                                                                             // tady se to taky pricita nebo nepricita ale nastavuje na 1 jako TRUE
        printf("Dealer cards %d + ?\nYour cards %d | aces: %d", dealerCards, playerCards, pace); // tady se vypise momentalni stav obou ucastniku Cerneho Jacka
        char ans;                                                                                // promena na ulozeni odpovedi
        if (pbj == 0 && dbj == 0)                                                                // podminka jestli nema nekdo blackjack
            ans = askForCard();                                                                  // tady se to pta jestli chce dostat dalsi kartu to je nahore uz zminena funkce
        while (ans == 'y' && (pbj == 0 && dbj == 0))                                             // tady je loop na pridavani karet hracovy
        {
            int value = cardReadValue(deck[0]); // tady to nacte hodnotu dalsi karty
            throwCard(deck, size);              // tady se smaze ta nacetla karta
            if (value == 11)                    // kdyz je to eso tak se to ulozi tady na pripadne odecitani
                pace++;

            playerCards += value; // tady to pricte hodnotu karty k hracovy

            if (playerCards > 21 && pace > 0) // tady je to s tema esama ze kdyz ma esa a prehodi 21 tak se 10 odecte tim padem se z esa stane 1
            {
                playerCards -= 10; // tady se to uz odecito
            }
            printf("\nYou got + %d, so you have %d | aces: %d", value, playerCards, pace); // tady to vypise soucasny stav hrace kolik ma karet co mu padlo a kolik ma es aby mohl vice riskovat protoze risk je zisk a tohle je royal casino

            if (playerCards > 21) // a kdyz nema esa tak se to ukonci
                break;            // konec

            ans = askForCard(); // kdyz nema ani jedno z toho tak to muze brat dal jest-li chce
        }

        if (ans != 'y' && playerCards <= 21 && (pbj == 0 || dbj == 0)) // tady si nabira do paklu dealer podminky / kdyz nikdo nema black jack nebo hrac neprehodil a ta prvni tam asi ani nemusi bejt vlastne ale necham si ji tam na vzpominku
        {
            dealerCards += firstCard;                                                                          // odhali se prvni karta co byla zakryta a pricte se mu do ruky
            printf("\nDealer is on turn\n\nhis first card was %d, and now he has %d", firstCard, dealerCards); // tady se vypise jeho stav aby hrac mohl taktizovat nebo uz vlastne nemuze uz dolital

            while (dealerCards < 17) // takovy bezny pravidlo ze dealer nesmi nad 17 to je vypocitany aby casino bylo v co nejvetsim zisku procentualne a kdyz je nad 17 tak se ukonci jelikoz s nim hraje jenom 1 clovek tak by ho mohl mozna zkusit dohodit to by stacilo prepsat jedno slovo
            {
                int value = cardReadValue(deck[0]); // tady se zas nacte ta karta hodnota
                throwCard(deck, size);              // tady se smaze ta nacetla karta
                if (value == 11)                    // tady se kontroluje to jestli to neni eso
                    dace++;                         // tady se to nakopne kdyby bylo
                dealerCards += value;               // tady se nahodi ta hodnota do jeho ruky
                if (dealerCards > 21 && dace > 0)   // check na to jestli nema eso kdyz prehodil
                {
                    dealerCards -= 10; // tady se ta karta zmeni z 11 na 1
                }
                printf("\nDealer got + %d, so he have %d", value, dealerCards); // vypise stav karet dealera
            }
        }
        // tady se rozhoduje kdo vyhral stacilo by tady zmenit par veci a casino by bylo ve 100% zisku takze tohle je open source
        if (playerCards == dealerCards) // kdyz maj stejne tak se provede tohle
        {
            printf("\n\n\n||    DRAW    , your balance is now %d||", funds); // vypise to tohle do konzole a nikomu se nic neodebere a zapne se hra znova
        }
        else if (playerCards > 21 || (dealerCards > playerCards && dealerCards < 21) || dbj == 1) // kdyz ma hrac vic jak 21 nebo ma dealer bliz k 21 nez hrac
        {
            funds -= bet;                                                         // tak se hracovy odecte cash $$$
            printf("\n\n\n|| YOU LOST %d, your balance is now %d||", bet, funds); // a vypuse to ze prohral
        }
        else // a tohle je ten zbytek pripadu ve kterych zvitezi hrac a ne casino
        {
            funds += bet;                                                         // pricteme zlataky
            printf("\n\n\n|| YOU  WON %d, your balance is now %d||", bet, funds); // a vypise se to ze dal win a kolik vyhral, kolik ma penez
        }
    }

    printf("\nYou have only 10$, to buy bus ticket away bye :)"); // kdyz bude mit min jak 10$ tak mu to hodi tuhle hlasku hezkou

    return 0; // tady se uknocuje main funkce
}

// a to je vsecko zacal jsem v 6:30 a ted je 17:18 :))))))))