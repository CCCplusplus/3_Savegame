#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>  
#include <vector>
#include <random>
#define MAXNAMESIZE 16

enum EWeapon
{
    none, sword, lance, hammer, bow 
};

//estructura de datos que deben persistir
struct SGameData
{
    char name[MAXNAMESIZE];
    EWeapon  currentWeapon;
    unsigned int  enemysKilled;
    int progress = 1;
    int path = 1;
    int hp = 50;
    int maxhp = 50;
    int attack = 6;
    int defense = 5;
    int skill = 3;
    int attackaccuracy1;
    int attack1power = attack;
    int attackaccuracy2;
    int attack2power;
};

struct Enemies
{
    std::string namea;
    int hp;
    int attack;
    int defense;
    int skill;
    int attack1power;
    int attackaccuracy1;
    int attack2power;
    int attackaccuracy2;
};

std::random_device rd;

void Log(const char* msg)
{
    std::cout << msg << "\n";
}

void LogN(const char* msg, SGameData Namae)
{
    std::cout << msg << " " << Namae.name << "\n";
}

void NLog(SGameData Namae, const char* msg)
{
    std::cout << Namae.name  << " " << msg << "\n";
}

void ELog(Enemies Namae, const char* msg)
{
    std::cout << Namae.namea << " " << msg << "\n";
}

int getRandomFrom(const std::vector<int>& numbers) {
    return numbers[rd() % numbers.size()];
}

int calculateDamage(int attackerDamage, int attackerAccuracy, int defenderSkill, int defenderDefense, int defenderHp, SGameData Namae, Enemies ENamae)
{
    ELog(ENamae, " Ataca!");
    // Calcula la precisión final en función de la habilidad del defensor.
    int finalAccuracy = attackerAccuracy - (defenderSkill / 3) * 10;

    // Asegura que la precisión final esté en el rango de 0 a 100.
    if (finalAccuracy < 0)
    {
        finalAccuracy = 0;
    }
    else if (finalAccuracy > 100)
    {
        finalAccuracy = 100;
    }

    // Determina si el ataque acierta.
    int hitRoll = rd() % 100;
    if (hitRoll > finalAccuracy)
    {
        NLog(Namae, " Esquiva el ataque rapidamente.");
        return defenderHp;
    }

    // Si el ataque acierta, calcula el daño.
    int damage = attackerDamage - defenderDefense;

    int criticalRoll = rd() % 100;
    if (criticalRoll < 10)  // 10% de posibilidades.
    {
        // Es un golpe crítico, por lo que multiplicamos el daño por 1.5.
        damage = static_cast<int>(round(damage * 1.5));
        Log("Es un Golpe Poderoso!");
    }

    // Asegura que el daño no sea negativo.
    if (damage <= 0)
    {
        damage = 0;
        NLog(Namae, " Logra defender el ataque");
    }

    // Aplica el daño al HP del defensor y devuelve el HP restante.
    int remainingHp = defenderHp - damage;
    std::cout << ENamae.namea << " baja " << damage << " puntos de hp " << Namae.name << " tiene " << remainingHp << " de hp" << "\n";

    if (remainingHp < 0)
    {
        remainingHp = 0;
    }
    return remainingHp;
}

int calculateDamageP(int attackerDamage, int attackerAccuracy, int defenderSkill, int defenderDefense, int defenderHp, SGameData Namae, Enemies ENamae)
{
    NLog(Namae, " Ataca!");

    // Calcula la precisión final en función de la habilidad del defensor.
    int finalAccuracy = attackerAccuracy - (defenderSkill / 3) * 10;

    // Asegura que la precisión final esté en el rango de 0 a 100.
    if (finalAccuracy < 0)
    {
        finalAccuracy = 0;
    }
    else if (finalAccuracy > 100)
    {
        finalAccuracy = 100;
    }

    // Determina si el ataque acierta.
    int hitRoll = rd() % 100;
    if (hitRoll >= finalAccuracy)
    {
        ELog(ENamae, " Logra esquivar.");
        return defenderHp;
    }

    // Si el ataque acierta, calcula el daño.
    int damage = attackerDamage - defenderDefense;

    int criticalRoll = rd() % 100;
    if (criticalRoll < 10)  // 10% de posibilidades.
    {
        // Es un golpe crítico, por lo que multiplicamos el daño por 1.5.
        damage = static_cast<int>(round(damage * 1.5));
        Log("Es un Golpe Poderoso!");
    }

    // Asegura que el daño no sea negativo.
    if (damage < 0)
    {
        damage = 0;
        NLog(Namae, " Detiene el ataque");
    }

    // Aplica el daño al HP del defensor y devuelve el HP restante.
    int remainingHp = defenderHp - damage;
    std::cout << Namae.name << " baja " << damage << " puntos de hp  " << ENamae.namea << "Tiene " << remainingHp << " de hp" << "\n";

    if (remainingHp < 0)
    {
        remainingHp = 0;
    }
    return remainingHp;
}

const char* weaponToString(EWeapon weapon)
{
    switch (weapon)
    {
    case none: return "ninguna";
    case sword: return "Espada y Escudo";
    case lance: return "Lanza";
    case hammer: return "Martillo de Guerra";
    case bow: return "Arco y flecha";
    default: return "Unknown Weapon";
    }
}

void tutorial(SGameData &data, std::fstream &save)
{

    NLog(data, " Despierta! No tenemos todo el dia.");
    Log("Por que me toca cuidar de los novatos?");
    Log("*Los gritos de Mel finalmente logran despertarte*");
    Log("Mel: Al fin, si sabes que no vinimos aqui para acampar verdad?");
    Log("Mel: Hoy tienes que probar que no eres un completo inutil.");
    Log("Mel: Pasando la prueba del bosque y recuperando la pocion de vitalidad que se encuentra en su centro.");
    Log("Mel: Entonces? que esperas? Mueve el tracero novato!");
    Log("*Tienes alguna pregunta para Mel? Presiona el numero que se indica para hacerla.*");
    
    std::string Answer;
    do
    {
        Log("1. 'Por que tan agresiva nena?'");
        Log("2. 'Por que la prueba es recuperar una pocion?'");
        Log("3. 'Algun consejo?'");
        Log("4. 'Hagamos esto!'");
        std::cin >> Answer;

        if (Answer == "1") 
        {
            Log("Mel: Por que tengo que perder mi tiempo y usar mis considerables habilidades para cuidar de mocosos, entiendes nene?");
        }
        else if (Answer == "2") 
        {
            Log("Mel: Es bastante util, tiene propiedades magicas que los humanos no podemos replicar.");
            Log("Mel: no solo puede curar enfermedades o heridas graves, las personas que lo beben se vuelven considerablemente mas fuertes.");
        }
        else if (Answer == "3") 
        {
            Log("Mel: Tu Segundo ataque siempre sera mas poderoso, pero tambien es mas probable que tus enemigos lo esquiven.");
            Log("Mel: Depende de ti decidir si vale la pena el riesgo.");
        }
        else if (Answer == "4") 
        {
            save.close();
            data.progress = 3;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "2" && Answer != "4");
    if (Answer == "2") 
    {
        do
        {
            Log("1. 'Por que tan agresiva nena?'");
            Log("2. 'Si es tan importante por que dejan que sea una prueba de graduacion?'");
            Log("3. 'Algun consejo?'");
            Log("4. 'Hagamos esto!'");

            std::cin >> Answer;

            if (Answer == "1")
            {
                Log("Mel: Por que tengo que perder mi tiempo y usar mis considerables habilidades para cuidar de mocosos, entiendes nene?");
            }
            else if (Answer == "2")
            {
                Log("Mel: Es cierto podriasmos mandar a aventureros mas experimentados a recolectarla, pero");
                Log("Mel: Esta area es bastante tranquila comparada con otra secciones del mundo.");
                Log("Mel: Si no puedes sobrevivir aqui, solo serias un estorbo como heroe.");
                Log("Mel: Asi que matamos dos pajaros de un tiro, conseguimos la pocion y vemos quien tiene lo necesario.");
                Log("Mel: Por cierto, dije que es un area tranquila pero... el 60% de los candidatos mueren en el examen; ten eso en mente.");
            }
            else if (Answer == "3")
            {
                Log("Mel: Tu ataque fuerte siempre sera mas poderoso, pero tambien es mas probable que tus enemigos lo esquiven.");
                Log("Mel: Depende de ti decidir si vale la pena el riesgo.");
            }
            else if (Answer == "4")
            {
                save.close();
                data.progress = 3;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else {
                Log("Respuesta no valida, porfavor vuelva a intentar.");
            }
        } while (Answer != "2" && Answer != "4");
    }
    if (Answer == "2") 
    {
        do
        {
            Log("1. 'Por que tan agresiva nena?'");
            Log("2. 'Quien pone la pocion en el centro del bosque?'");
            Log("3. 'Algun consejo?'");
            Log("4. 'Hagamos esto!'");
            std::cin >> Answer;

            if (Answer == "1")
            {
                Log("Mel: Por que perdiedno mi tiempo y usando mis considerables habilidades para cuidar de un mocoso, entiendes nene?");
            }
            else if (Answer == "2")
            {
                Log("Mel: No se! Hadas porbablmente, siempre estan haciendo cosas raras, a quien le importa?");
                Log("Mel: Lo importante es que tu tienes que ir a recuperarla.");
            }
            else if (Answer == "3")
            {
                Log("Mel: Tu Segundo ataque siempre sera mas poderoso, pero tambien es mas probable que tus enemigos lo esquiven.");
                Log("Mel: Depende de ti decidir si vale la pena el riesgo.");
            }
            else if (Answer == "4")
            {
                save.close();
                data.progress = 3;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else {
                Log("Respuesta no valida, porfavor vuelva a intentar.");
            }
        } while (Answer != "4");

        Log("Quieres continuar?");
        do
        {
            Log("*Presiona Q para salir y C para continuar");
            std::cin >> Answer;

            if (Answer == "C" || Answer == "c") 
            {
                Log("Continuando");
            }
            else if (Answer == "Q" || Answer == "q")
            {
                Log("Salvando.");
                Log("Saliendo del juego");
                exit(0);
            }
            else
            {
                Log("Respuesta no valida, porfavor vuelva a intentar.");
            }
        } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
    }
}

void WeaponChoice(SGameData& data, std::fstream& save)
{
    Log("Mel: Excelente, recuerdame otra vez cual es tu arma?");
    std::string Answer;
    do
    {
        Log("*Elige tu Arma*");
        Log("1. Sword *+attack +defense*");
        Log("2. Lance *+attack +defense +skill*");
        Log("3. Hammer *++attack +defense -skill*");
        Log("4. Bow * +attack - defense ++skill*");
        std::cin >> Answer;

        if (Answer == "1")
        {
            Log("Mel: Tipico, Aqui tienes, una espada con su escudo.");
            NLog(data, "Obtiene una espada y un escudo!");
            Log("*Attack + 2*");
            Log("*Defense + 2*");
            save.close();
            data.currentWeapon = EWeapon::sword;
            data.progress = 4;
            data.attack += 2;
            data.defense += 2;
            data.attackaccuracy1 = 100;
            data.attack1power = data.attack;
            data.attackaccuracy1 = 90;
            data.attack2power = data.attack1power + 2;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (Answer == "2")
        {
            Log("Mel: Las personas dicen que las lanzas son para cobardes, yo creo que les falta habilidad para usarlas. Aqui tienes.");
            NLog(data, "Obtiene una lanza!");
            Log("*Attack + 2*");
            Log("*Defense + 1*");
            Log("*SKill + 1*");
            save.close();
            data.currentWeapon = EWeapon::lance;
            data.progress = 4;
            data.attack += 2;
            data.defense += 1;
            data.skill += 1;
            data.attackaccuracy1 = 100;
            data.attack1power = data.attack;
            data.attackaccuracy1 = 80;
            data.attack2power = data.attack1power + 4;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (Answer == "3")
        {
            Log("Mel: Un gran martillo de guerra, compansando algo nene? Aqui tienes.");
            NLog(data, "Obtiene un martillo!");
            Log("*Attack + 4*");
            Log("*Defense + 1*");
            Log("*Skill -2");
            save.close();
            data.currentWeapon = EWeapon::hammer;
            data.progress = 4;
            data.attack += 4;
            data.defense += 1;
            data.skill -= 2;
            data.attackaccuracy1 = 90;
            data.attack1power = data.attack;
            data.attackaccuracy1 = 70;
            data.attack2power = data.attack1power + 6;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (Answer == "4")
        {
            Log("Mel: Un arquero en las lineas frontales? Te gusta el peligro eh?.");
            NLog(data, "Obtiene arco y flechas!");
            Log("*Attack + 2*");
            Log("*Defense - 2*");
            Log("*Skill +2");
            save.close();
            data.currentWeapon = EWeapon::bow;
            data.progress = 4;
            data.attack += 2;
            data.defense -= 2;
            data.skill += 2;
            data.attackaccuracy1 = 100;
            data.attack1power = data.attack;
            data.attackaccuracy1 = 75;
            data.attack2power = data.attack1power + 5;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "1" && Answer != "2" && Answer != "3" && Answer != "4");

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}
void Stage1(SGameData& data, std::fstream& save) 
{
    Log("Mel: Muy bien. Recuerda tu entrenamiento e intenta no morir.");
    Log("Mel: Oh! una cosa mas, ni se te ocurra beberte la pocima!");
    Log("Mel: Es propiedad del gremio y se considerara como un traidor a cualquiera que la beba sin permiso.");
    Log("*Con esa ultima advertencia te pones en marcha*");
    Log("Despues de un tiempo te encuentras con un letrero marcando el incio de la prueba y no mucho despues una difurcacion en el camino, en ambos caminos hay un pequeño letro con una 'X' roja dibujada.");
    Log("*Que camino quieres tomar?*");
    Log("1. *Izquierda*");
    Log("2. *Derecha*");
    std::string Answer;
    do
    {
        std::cin >> Answer;
        if (Answer == "1") 
        {
            NLog(data, "Decide ir a la Izquierda");
            save.close();
            data.progress = 5;
            data.path = 1;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (Answer == "2") 
        {
            NLog(data, "Decide ir a la Derecha");
            save.close();
            data.progress = 5;
            data.path = 2;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else 
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "1" && Answer != "2");

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void GoblinAttack(SGameData& data, std::fstream& save)
{
    Enemies Goblin1;
    Enemies Goblin2;
    Enemies Goblin3;
    Goblin1.namea = "Goblin Grunt";
    Goblin1.hp = 15;
    Goblin1.attack = 8;
    Goblin1.defense = 2;
    Goblin1.skill = 2;
    Goblin1.attack1power = Goblin1.attack;
    Goblin1.attackaccuracy1 = 90;
    Goblin1.attack2power = Goblin1.attack + 3;
    Goblin1.attackaccuracy2 = 75;

    Goblin2.namea = "Goblin Leader";
    Goblin2.hp = 16;
    Goblin2.attack = 9;
    Goblin2.defense = 3;
    Goblin2.skill = 3;
    Goblin2.attack1power = Goblin2.attack;
    Goblin2.attackaccuracy1 = 100;
    Goblin2.attack2power = Goblin2.attack + 3;
    Goblin2.attackaccuracy2 = 75;

    Goblin3.namea = "Goblin Brawler";
    Goblin3.hp = 15;
    Goblin3.attack = 8;
    Goblin3.defense = 2;
    Goblin3.skill = 2;
    Goblin3.attack1power = Goblin3.attack;
    Goblin3.attackaccuracy1 = 90;
    Goblin3.attack2power = Goblin3.attack + 3;
    Goblin3.attackaccuracy2 = 75;

    NLog(data,"Sigue el camino del bosque cuando");
    Log("De los arbustos saltan una tropa de Goblins!");
    Log("Sus alaridos y gritos no tienen ningun sentido, pero la manera en la que blanden sus cuchillos es inconfundible");
    NLog(data, "Seprepara para el combate.");

    std::string Answer;
    do
    {
        std::cout << data.name << " Tiene " << data.hp << "\n";
        Log("*Elige un ataque*");
        Log("1. Ataque Normal");
        Log("2. Ataque Fuerte");
        
        std::cin >> Answer;

        if (Answer == "1")
        {
            std::string Target;
            
            {
            Log("*Elige un objetivo*");
            Log("1. Goblin Grunt");
            Log("2. Goblin Leader");
            Log("3. Goblin Brawler");
            std::cin >> Target;

            if (Target == "1" && Goblin1.hp > 0) {
                Goblin1.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Goblin1.skill, Goblin1.defense, Goblin1.hp, data, Goblin1);
                if (Goblin1.hp <= 0) {
                    Goblin1.hp = 0;
                    Log("Goblin Grunt ha sido derrotado.");
                }
            }
            else if (Target == "2" && Goblin2.hp > 0) {
                Goblin2.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Goblin2.skill, Goblin2.defense, Goblin2.hp, data, Goblin2);
                if (Goblin2.hp <= 0) {
                    Goblin2.hp = 0;
                    Log("Goblin Leader ha sido derrotado.");
                }
            }
            else if (Target == "3" && Goblin3.hp > 0) {
                Goblin3.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Goblin3.skill, Goblin3.defense, Goblin3.hp, data, Goblin3);
                if (Goblin3.hp <= 0) {
                    Goblin3.hp = 0;
                    Log("Goblin Brawler ha sido derrotado.");
                }
            }
            else {
                Log("El objetivo ya ha sido derrotado o el número introducido es incorrecto, elige otro objetivo.");
            }
            }
        }
        else if (Answer == "2")
        {
            std::string Target;
            {
                Log("*Elige un objetivo*");
                Log("1. Goblin Grunt");
                Log("2. Goblin Leader");
                Log("3. Goblin Brawler");
                std::cin >> Target;

                if (Target == "1" && Goblin1.hp > 0) {
                    Goblin1.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Goblin1.skill, Goblin1.defense, Goblin1.hp, data, Goblin1);
                    if (Goblin1.hp <= 0) {
                        Goblin1.hp = 0;
                        Log("Goblin Grunt ha sido derrotado.");
                    }
                }
                else if (Target == "2" && Goblin2.hp > 0) {
                    Goblin2.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Goblin2.skill, Goblin2.defense, Goblin2.hp, data, Goblin2);
                    if (Goblin2.hp <= 0) {
                        Goblin2.hp = 0;
                        Log("Goblin Leader ha sido derrotado.");
                    }
                }
                else if (Target == "3" && Goblin3.hp > 0) {
                    Goblin3.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Goblin3.skill, Goblin3.defense, Goblin3.hp, data, Goblin3);
                    if (Goblin3.hp <= 0) {
                        Goblin3.hp = 0;
                        Log("Goblin Brawler ha sido derrotado.");
                    }
                }
                else {
                    Log("El objetivo ya ha sido derrotado o el número introducido es incorrecto, elige otro objetivo.");
                }
            }
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
            continue;
        }

        // Los goblins atacan
        if (data.hp > 0 && (Goblin1.hp > 0 || Goblin2.hp > 0 || Goblin3.hp > 0))
        {
            srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios

            if (Goblin1.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Goblin1.attack1power, Goblin1.attackaccuracy1, data.skill, data.defense, data.hp, data, Goblin1);
                }
                else {
                    data.hp = calculateDamage(Goblin1.attack2power, Goblin1.attackaccuracy2, data.skill, data.defense, data.hp, data, Goblin1);
                }
            }

            if (Goblin2.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Goblin2.attack1power, Goblin2.attackaccuracy1, data.skill, data.defense, data.hp, data, Goblin2);
                }
                else {
                    data.hp = calculateDamage(Goblin2.attack2power, Goblin2.attackaccuracy2, data.skill, data.defense, data.hp, data, Goblin2);
                }
            }

            if (Goblin3.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Goblin3.attack1power, Goblin3.attackaccuracy1, data.skill, data.defense, data.hp, data, Goblin3);
                }
                else {
                    data.hp = calculateDamage(Goblin3.attack2power, Goblin3.attackaccuracy2, data.skill, data.defense, data.hp, data, Goblin3);
                }
            }

            if (data.hp <= 0) {
                save.close();
                data.currentWeapon = EWeapon::none;
                data.enemysKilled = 0;
                data.progress = 1;
                data.path = 1;
                data.hp = 50;
                data.maxhp = 50;
                data.attack = 6;
                data.defense = 5;
                data.skill = 2;
                data.attackaccuracy1 = 100;
                data.attack1power = data.attack;
                data.attackaccuracy2 = 100;
                data.attack2power = data.attack + 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
                Log("Has muerto");
                Log("No pudiste probar que tenias lo necesario para ser un heroe");
                Log("Despues de un tiempo, Mel se llevo tus cosas utiles y quemo las demas.");
                Log("Fin.");
                save.close();
                exit(0);
            }
        }

    } while (data.hp > 0 && (Goblin1.hp > 0 || Goblin2.hp > 0 || Goblin3.hp > 0));

    Log("Todos los goblins han sido derrotados, has ganado el combate.");
    Log("*Despues de la batalla tus stats suben!*");
    Log("*Atack +2*");
    Log("*Defense +2*");
    save.close();
    data.enemysKilled += 3;
    data.progress = 6;
    data.attack += 2;
    data.defense += 2;
    data.hp;
    save.open("data.sav", std::ios::out);
    if (save.is_open())
    {
        //dumpear la estructura data
        save.seekp(0, std::ios::beg);
        save.write((const char*)&data, sizeof(SGameData));
    }
    else
    {
        Log("no se pudo crear el archivo");
    }

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void WispAttack(SGameData& data, std::fstream& save) 
{
    Enemies Wisp1;
    Enemies Wisp2;
    Enemies Wisp3;
    Wisp1.namea = "Wisp Left";
    Wisp1.hp = 10;
    Wisp1.attack = 6;
    Wisp1.defense = 1;
    Wisp1.skill = 6;
    Wisp1.attack1power = Wisp1.attack;
    Wisp1.attackaccuracy1 = 100;
    Wisp1.attack2power = Wisp1.attack + 7;
    Wisp1.attackaccuracy2 = 60;

    Wisp2.namea = "Wisp Middle";
    Wisp2.hp = 10;
    Wisp2.attack = 6;
    Wisp2.defense = 1;
    Wisp2.skill = 6;
    Wisp2.attack1power = Wisp2.attack;
    Wisp2.attackaccuracy1 = 100;
    Wisp2.attack2power =  Wisp2.attack + 7;
    Wisp2.attackaccuracy2 = 60;

    Wisp3.namea = "Wisp Right";
    Wisp3.hp = 10;
    Wisp3.attack = 6;
    Wisp3.defense = 1;
    Wisp3.skill = 6;
    Wisp3.attack1power = Wisp3.attack;
    Wisp3.attackaccuracy1 = 100;
    Wisp3.attack2power = Wisp3.attack + 7;
    Wisp3.attackaccuracy2 = 60;

    NLog(data, "Sigue el camino del bosque cuando");
    Log("tres pequeños resplandores caen del cielo, son como enormes lucirnagas que brillan aun bajo la luz del sol");
    NLog(data, "Escucha ricitas que se vuelven mas fuerte entre mas se acercan.");
    LogN("De pronto uno de los tres resplandores lanza una llama hacia", data);
    NLog(data, "Logra esquivarlo, Parece que los tres resplandores son wisps y son bastante agresivos");
    NLog(data, "Se prepara para el combate.");

    std::string Answer;
    do
    {
        std::cout << data.name << " Tiene " << data.hp << "\n";
        Log("*Elige un ataque*");
        Log("1. Ataque Normal");
        Log("2. Ataque Fuerte");

        std::cin >> Answer;

        if (Answer == "1")
        {
            std::string Target;

            {
                Log("*Elige un objetivo*");
                Log("1. Wisp Left");
                Log("2. Wisp Middle");
                Log("3. Wisp Right");
                std::cin >> Target;

                if (Target == "1" && Wisp1.hp > 0) {
                    Wisp1.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Wisp1.skill, Wisp1.defense, Wisp1.hp, data, Wisp1);
                    if (Wisp1.hp <= 0) {
                        Wisp1.hp = 0;
                        Log("Wisp Left ha sido derrotado.");
                    }
                }
                else if (Target == "2" && Wisp2.hp > 0) {
                    Wisp2.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Wisp2.skill, Wisp2.defense, Wisp2.hp, data, Wisp2);
                    if (Wisp2.hp <= 0) {
                        Wisp2.hp = 0;
                        Log("Wisp Middle ha sido derrotado.");
                    }
                }
                else if (Target == "3" && Wisp3.hp > 0) {
                    Wisp3.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Wisp3.skill, Wisp3.defense, Wisp3.hp, data, Wisp3);
                    if (Wisp3.hp <= 0) {
                        Wisp3.hp = 0;
                        Log("Wisp Right ha sido derrotado.");
                    }
                }
                else {
                    Log("El objetivo ya ha sido derrotado o el número introducido es incorrecto, elige otro objetivo.");
                }
            }
        }
        else if (Answer == "2")
        {
            std::string Target;
            {
                Log("*Elige un objetivo*");
                Log("1. Wisp Left");
                Log("2. Wisp Middle");
                Log("3. Wisp Right");
                std::cin >> Target;

                if (Target == "1" && Wisp1.hp > 0) {
                    Wisp1.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Wisp1.skill, Wisp1.defense, Wisp1.hp, data, Wisp1);
                    if (Wisp1.hp <= 0) {
                        Wisp1.hp = 0;
                        Log("Wisp Left ha sido derrotado.");
                    }
                }
                else if (Target == "2" && Wisp2.hp > 0) {
                    Wisp2.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Wisp2.skill, Wisp2.defense, Wisp2.hp, data, Wisp2);
                    if (Wisp2.hp <= 0) {
                        Wisp2.hp = 0;
                        Log("Wisp Middle ha sido derrotado.");
                    }
                }
                else if (Target == "3" && Wisp3.hp > 0) {
                    Wisp3.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Wisp3.skill, Wisp3.defense, Wisp3.hp, data, Wisp3);
                    if (Wisp3.hp <= 0) {
                        Wisp3.hp = 0;
                        Log("Wisp Right ha sido derrotado.");
                    }
                }
                else {
                    Log("El objetivo ya ha sido derrotado o el número introducido es incorrecto, elige otro objetivo.");
                }
            }
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
            continue;
        }

        
        if (data.hp > 0 && (Wisp1.hp > 0 || Wisp2.hp > 0 || Wisp3.hp > 0))
        {
            srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios

            if (Wisp1.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Wisp1.attack1power, Wisp1.attackaccuracy1, data.skill, data.defense, data.hp, data, Wisp1);
                }
                else {
                    data.hp = calculateDamage(Wisp1.attack2power, Wisp1.attackaccuracy2, data.skill, data.defense, data.hp, data, Wisp1);
                }
            }

            if (Wisp2.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Wisp2.attack1power, Wisp2.attackaccuracy1, data.skill, data.defense, data.hp, data, Wisp2);
                }
                else {
                    data.hp = calculateDamage(Wisp2.attack2power, Wisp2.attackaccuracy2, data.skill, data.defense, data.hp, data, Wisp2);
                }
            }

            if (Wisp3.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Wisp3.attack1power, Wisp3.attackaccuracy1, data.skill, data.defense, data.hp, data, Wisp3);
                }
                else {
                    data.hp = calculateDamage(Wisp3.attack2power, Wisp3.attackaccuracy2, data.skill, data.defense, data.hp, data, Wisp3);
                }
            }

            if (data.hp <= 0) {
                save.close();
                data.currentWeapon = EWeapon::none;
                data.enemysKilled = 0;
                data.progress = 1;
                data.path = 1;
                data.hp = 50;
                data.maxhp = 50;
                data.attack = 6;
                data.defense = 5;
                data.skill = 2;
                data.attackaccuracy1 = 100;
                data.attack1power = data.attack;
                data.attackaccuracy2 = 100;
                data.attack2power = data.attack + 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
                Log("Has muerto");
                Log("No pudiste probar que tenias lo necesario para ser un heroe");
                Log("Despues de un tiempo, Mel se llevo tus cosas utiles y quemo las demas.");
                Log("Fin.");
                save.close();
                exit(0);
            }
        }

    } while (data.hp > 0 && (Wisp1.hp > 0 || Wisp2.hp > 0 || Wisp3.hp > 0));

    Log("Todos los Wisps han sido derrotados, has ganado el combate.");
    Log("*Despues de la batalla tus stats suben.*");
    Log("*Skill +3*");
    save.close();
    data.enemysKilled += 3;
    data.progress = 6;
    data.skill += 3;
    data.hp;
    save.open("data.sav", std::ios::out);
    if (save.is_open())
    {
        //dumpear la estructura data
        save.seekp(0, std::ios::beg);
        save.write((const char*)&data, sizeof(SGameData));
    }
    else
    {
        Log("no se pudo crear el archivo");
    }

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void Stage2(SGameData& data, std::fstream& save) 
{
    NLog(data, " se siente orgulloso por haber sobrevivido a su primer batalla.");
    std::cout << data.name << " tiene " << data.hp << "  de vida";
    Log("*Continuas por el camino del bosque hasta que, encuentras otra bifurcacion*");
    Log("A la izquierda puede ver un camino marcado con un letrero con un circulo dibujado");
    Log("A la derecha puede ver un camino marcado con un letrero con una X dibujada");
    Log("Un Lago resplandeciente se encuentra no muy lejos");
    std::string Answer;
    int lakeVisit = 0;
    do
    {
        Log("*Que camino quieres tomar?*");
        Log("1. *Izquierda*");
        Log("2. *Derecha*");
        Log("3. *Investigar lago*");

        std::cin >> Answer;
        if (Answer == "1")
        {
            NLog(data, "Decide ir a la Izquierda");
            save.close();
            data.progress = 7;
            data.path = 1;
            data.hp;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (Answer == "2")
        {
            NLog(data, "Decide ir a la Derecha");
            save.close();
            data.progress = 7;
            data.path = 2;
            data.hp;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (lakeVisit == 0 && Answer == "3")
        {
            lakeVisit = 1;
            Log("Ninfa: En el momento que te acercas a la orilla del lago el agua empieza a retraerse");
            Log("Ninfa: En segundos el agua se empieza a acumular y a subir como si se estuviera formando una ola gigante.");
            Log("Ninfa: Pero en lugar de eso, del agua se materializa una gigante mujer! Es una ninfa y parece ser bastante poderosa.");
            NLog(data, " Valiente aspirante a heroe, yo soy la protectora de los lagos y rios de este bosque.");
            Log("Ninfa: Si me lo pides, puedo ayudarte en tu viaje.");
            std::string Response;
            do
            {
                
                Log("*Sientes que la manera en la que respondas va a definir la cantidad de ayuda que recibas.*");
                Log("*Como le quieres responder a la ninfa?*");
                Log("1. 'Supongo que puedo dejar que me ayudes, nenota.'");
                Log("2. 'Porfavor ayudeme en mi viaje'");
                Log("3. *Arodillandote primer dices* 'Seria un honor su pudiera ayudarme en mi viaje Guardiana.'");
                Log("4. 'No creo nada de lo que dices, tu debes ser un mounstro del lago! ponte en guardia!'");
                std::cin >> Response;

                if (Response == "1") 
                {
                    Log("Ninfa: ... muy bien");
                    Log("*te sientes lleno de vitalidad*");
                    Log("*HP + 20*");
                    data.hp += 20;
                    if (data.hp > data.maxhp) {
                        data.hp = data.maxhp;
                    }
                    Log("No voy a fingir que no eres un poco... decepcionante pero, te deseo suerte.");
                }
                else if (Response == "2") 
                {
                    LogN("Ninfa: Consedere tu deseo valiente", data);
                    Log("*La energia llena tu cuerpo te sientes completamente recuperado");
                    Log("*HP Max*");
                    data.hp = data.maxhp;
                    Log("Ninfa: Ahora ve, orare por que vuelvas triufal");
                }
                else if (Response == "3")
                {
                    Log("*Escuchas una pequeña risa complacida*");
                    Log("Ninfa: No tenias que ir tan lejos, deberias guardar tus ruegos para las deidades de agua.");
                    Log("Ninfa: ... pero no negare que me has hecho feliz");
                    LogN("Ninfa: Muy bien devoto", data);
                    Log("Ninfa: Te dare mi mejor bendicion");
                    Log("*Sientes un increible poder por todo tu cuerpo*");
                    Log("*tu HP supera el maximo!*");
                    data.maxhp = 60;
                    data.hp = data.maxhp;
                    LogN("Ninfa: Levantate, futuro heroe", data);
                    Log("Ninfa: Se que completaras tu mison!");
                }
                else if (Response == "4")
                {
                    Log("Ninfa: ... Eres tonto? Lento? Tus padres son primos o algo?");
                    Log("Ninfa: Mirame! soy 20 veces más grande que tu y estoy junto a mi fuente de poder.");
                    std::cout << "Ninfa: y tu tienes un " << weaponToString(data.currentWeapon) << " Que vas a hacer con eso?" << "\n";
                    Log("Ninfa: Golpear el agua mientras te ahogo?");
                    Log("Ninfa: Sabes que... no tengo tiempo para esto. Adios.");
                    Log("*Sin decir mas la ninfa desaparece*");
                    Log("*Eso pudo haber salido mejor.*");
                }
                else {
                    Log("Respuesta no valida, porfavor vuelva a intentar.");
                }
            } while (Response != "1" && Response != "2" && Response != "3" && Response != "4");
        }
        else if (lakeVisit == 1 && Answer == "3") 
        {
            Log("Sera mejor que ya no molestes a la ninfa");
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "1" && Answer != "2");

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void Decision(SGameData& data, std::fstream& save) 
{
    Log("El sendero derecho te lleva por otra seccion del bosque rodeada por arboles");
    Log("El camino es tranquilo, pero de la nada un pequeño duende aparece en el toncon de un arbol");
    Log("Duende: Hola Soy GlabGlamer! el maestro de este bosque y vengo a presentarte un desafio");
    NLog(data, "*Nunca habia estado tan confundido en su vida...*");
    Log("GlabGlamer: Es muy sencillo realmente todo lo que tienes que hacer es responder mi acertijo!");
    Log("GlabGlamer: Si lo contestas bien te daré una gran recompensa!");
    Log("GlabGlamer: Si fallas tu castigo te llenara de verguenza!");
    Log("GlabGlamer: hasta un bebe podria entender o si no mi nombre no es GlabGlamer! Que dices aventurero?");

    std::string answer;
    std::string answer2;
    std::string answer3;
    Log("*Como contestas?*");
    Log("1.'Respondere tu acertijo oh Gran GlabGlamer'");
    Log("2.'Estoy muy asustado para contestar oh maginifico GlabGlamer!'");
    Log("3. 'Perdon no entiendo que debo hacer?'");
    Log("4. *Ataca*");
    Log("Cualquier otra tecla. *vete sin decir nada.*");
    std::cin >> answer;

    if (answer == "1") 
    {
        Log("GlabGlamer: Aprecio tu velentia! Muy bien escucha las palabras de GlabGlamer");
        Log("En la sala de fuegos eternos. una salamandra, un dragon y un fenix. Discutian acaloradamente sobre quien de ellos poseia el fuego mas caliente.");
        Log("La salamandra dijo: 'Mi fuego nace de la alquimia, de mi se escriben cuentos de transformacion. Mi cuerpo siempre esta caliente, incluso en el invierno mas frio.'");
        Log("El dragon rugio: 'Mi aliento escupe fuego, capaz de derretir acero. Mis llamas pueden arrasar montañas y reducir ciudades enteras a cenizas.'");
        Log("El fenix entonces replicó: 'Naci de las cenizas, mi cuerpo es una llama viviente. Cuando muero, exploto en un incendio tan intenso que quema hasta a la muerte'");
        Log("GlabGlamer quien escuchaba les dijo: 'Todos tienen un buen punto, diria yo que el fuego mas caliente le pertenece aquel que caliente el invierno, pueda derretirlo todo y sus llamas sean parte del ciclo de la vida y la muerte.");
        Log("Las tres criaturas lo pensaron y asintieron aceptando mi sabiduría, dejando la sala fuimos a comer unas rocas de lava");
        Log("pero la pregunta para ti se queda, que ente tiene el fuego mas caliente?");

        std::cin >> answer2;

        if (answer2 == "sol" || answer2 == "SOL" || answer2 == "Sol") 
        {
            Log("GlabGlamer: Correcto! el fuego mas caliente viene del sol, osea en su superficie no los rayos suelen ser hasta cuatro veces mas calientes pero eso a nadie le importa.");
            Log("GlabGlamer: Tu subiduria ha impresionado a GlabGlamer y por ello tienes mi bendicion");
            Log("*Todos tus stats suben dramaticamente*");
            Log("*Hp +5*");
            Log("*Attack +2*");
            Log("*defense +2*");
            Log("*Skill +2*");
            Log("GlabGlamer: Buena suerte aventurero!");
            save.close();
            data.progress = 8;
            data.attack += 2;
            data.defense += 2;
            data.skill += 2;
            data.maxhp += 5;
            data.hp = data.maxhp;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (answer2 == "GlabGlamer") 
        {
            Log("GlabGlamer: GlabGlamer? dijiste GlabGlamer?! Eso es... CORRECTO!!!");
            Log("GlabGlamer: GlabGlamer es la respuesta a todas las cosas!!! Toma tu premio");
            Log("*Todos tus stats suben");
            Log("*Hp +2*");
            Log("*Attack +1*");
            Log("*defense +1*");
            Log("*Skill +1*");
            Log("GlabGlamer: La fuerza de GlabGlamer esta contigo!");
            save.close();
            data.progress = 8;
            data.attack += 1;
            data.defense += 1;
            data.skill += 1;
            data.maxhp += 2;
            data.hp = data.maxhp;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else 
        {
            Log("GlabGlamer: Oh ho ho! eso es... INCORRECTO");
            Log("GlabGlamer: Toma esto perdedor");
            Log("*GlabGlamer te dispara un rayo y desaparece, por un segundo no entiendes que paso pero luego miras tu arma*");
            std::cout << "Tu " << weaponToString(data.currentWeapon) << "esta brillando \n";

            std::random_device rd;

            // Crea un objeto de distribución para cada conjunto de números
            std::vector<int> list1 = { 2, 3, 4 };
            std::vector<int> list2 = { 1, 3, 4 };
            std::vector<int> list3 = { 1, 2, 4 };
            std::vector<int> list4 = { 1, 2, 3 };

            if (data.currentWeapon = EWeapon::sword) 
            {
                int random1 = list1[rd() % list1.size()];

                if (random1 == 2) 
                {
                    Log("Tu espada y escudo cambian a una lanza");
                    Log("*pierdes los beneficios de tus espada*");
                    Log("*Attack -2*");
                    Log("*Defense -2*");
                    Log("*Obtienes los beneficios de la lanza*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense +0*");
                    Log("*Skill +1*");
                    save.close();
                    data.currentWeapon = EWeapon::lance;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense += 0;
                    data.skill += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 75;
                    data.attack2power = data.attack1power + 4;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random1 == 3) 
                {
                    Log("Tu espada y escudo cambian a un martillo");
                    Log("*pierdes los beneficios de tus espada*");
                    Log("*Attack -2*");
                    Log("*Defense -2*");
                    Log("*Obtienes los beneficios del martillo*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +2*");
                    Log("*Defense +0*");
                    Log("*Skill -2*");
                    save.close();
                    data.currentWeapon = EWeapon::hammer;
                    data.progress = 8;
                    data.attack += 2;
                    data.defense += 0;
                    data.skill -= 2;
                    data.attackaccuracy1 = 80;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 70;
                    data.attack2power = data.attack1power + 6;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random1 == 4) 
                {
                    Log("Tu espada y escudo cambian a un arco y flecha");
                    Log("*pierdes los beneficios de tus espada*");
                    Log("*Attack -2*");
                    Log("*Defense -2*");
                    Log("*Obtienes los beneficios del arco y flecha*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense -2*");
                    Log("*Skill +1*");
                    save.close();
                    data.currentWeapon = EWeapon::bow;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense -= 2;
                    data.skill += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 75;
                    data.attack2power = data.attack1power + 5;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
            }
            else if (data.currentWeapon = EWeapon::lance) 
            {
                int random2 = list2[rd() % list2.size()];

                if (random2 == 1)
                {
                    Log("Tu lanza cambian a una espada y un escudo");
                    Log("*pierdes los beneficios de tus lanza*");
                    Log("*Attack -2*");
                    Log("*Defense -1*");
                    Log("*Skill -1*");
                    Log("*Obtienes los beneficios de la espada y el escudo*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense +1*");
                    save.close();
                    data.currentWeapon = EWeapon::sword;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 85;
                    data.attack2power = data.attack1power + 2;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random2 == 3)
                {
                    Log("Tu lanza cambian a un martillo");
                    Log("*pierdes los beneficios de tus lanza*");
                    Log("*Attack -2*");
                    Log("*Defense -1*");
                    Log("*Skill -1*");
                    Log("*Obtienes los beneficios del martillo*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +2*");
                    Log("*Defense +0*");
                    Log("*Skill -2*");
                    save.close();
                    data.currentWeapon = EWeapon::hammer;
                    data.progress = 8;
                    data.attack += 2;
                    data.defense += 0;
                    data.skill -= 2;
                    data.attackaccuracy1 = 80;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 70;
                    data.attack2power = data.attack1power + 6;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random2 == 4)
                {
                    Log("Tu lanza cambian a un arco y flecha");
                    Log("*pierdes los beneficios de tus lanza*");
                    Log("*Attack -2*");
                    Log("*Defense -1*");
                    Log("*Skill -1*");
                    Log("*Obtienes los beneficios del arco y flecha*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense -2*");
                    Log("*Skill +1*");
                    save.close();
                    data.currentWeapon = EWeapon::bow;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense -= 2;
                    data.skill += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 75;
                    data.attack2power = data.attack1power + 5;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
            }
            else if (data.currentWeapon = EWeapon::hammer)
            {
                std::vector<int> list3 = { 1, 2, 4 };

                int random3 = list3[rd() % list3.size()];

                if (random3 == 1)
                {
                    Log("Tu Martillo cambian a una espada y un escudo");
                    Log("*pierdes los beneficios de tus martillo*");
                    Log("*Attack -3*");
                    Log("*Defense -1*");
                    Log("*Skill +2*");
                    Log("*Obtienes los beneficios de la espada y el escudo*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense +1*");
                    save.close();
                    data.currentWeapon = EWeapon::sword;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 85;
                    data.attack2power = data.attack1power + 2;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random3 == 2)
                {
                    Log("Tu marillo cambian a un lanza");
                    Log("*pierdes los beneficios de tus martillo*");
                    Log("*Attack -3*");
                    Log("*Defense -1*");
                    Log("*Skill +2*");
                    Log("*Obtienes los beneficios del lanza*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense +0*");
                    Log("*Skill +1*");
                    save.close();
                    data.currentWeapon = EWeapon::lance;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense += 0;
                    data.skill += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 75;
                    data.attack2power = data.attack1power + 4;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random3 == 4)
                {
                    Log("Tu martillo cambian a un arco y flecha");
                    Log("*pierdes los beneficios de tus martillo*");
                    Log("*Attack -3*");
                    Log("*Defense -1*");
                    Log("*Skill +2*");
                    Log("*Obtienes los beneficios del arco y flecha*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense -2*");
                    Log("*Skill +1*");
                    save.close();
                    data.currentWeapon = EWeapon::bow;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense -= 2;
                    data.skill += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 75;
                    data.attack2power = data.attack1power + 5;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
            }
            else if (data.currentWeapon = EWeapon::bow)
            {
                std::vector<int> list4 = { 1, 2, 3 };

                int random4 = list4[rd() % list4.size()];

                if (random4 == 1)
                {
                    Log("Tu arco y flecha cambian a una espada y un escudo");
                    Log("*pierdes los beneficios de tu arco y flecha*");
                    Log("*Attack -2*");
                    Log("*Defense +2*");
                    Log("*Skill -2*");
                    Log("*Obtienes los beneficios de la espada y el escudo*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense +1*");
                    save.close();
                    data.currentWeapon = EWeapon::sword;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 85;
                    data.attack2power = data.attack1power + 2;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random4 == 2)
                {
                    Log("Tu arco y flecha cambian a un lanza");
                    Log("*pierdes los beneficios de tu arco y flecha*");
                    Log("*Attack -2*");
                    Log("*Defense +2*");
                    Log("*Skill -2*");
                    Log("*Obtienes los beneficios del lanza*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +1*");
                    Log("*Defense +0*");
                    Log("*Skill +1*");
                    save.close();
                    data.currentWeapon = EWeapon::lance;
                    data.progress = 8;
                    data.attack += 1;
                    data.defense += 0;
                    data.skill += 1;
                    data.attackaccuracy1 = 90;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 75;
                    data.attack2power = data.attack1power + 4;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (random4 == 3)
                {
                    Log("Tu arco y flecha cambian a martillo");
                    Log("*pierdes los beneficios de tus martillo*");
                    Log("*Attack -2*");
                    Log("*Defense +2*");
                    Log("*Skill -2*");
                    Log("*Obtienes los beneficios del martillo*");
                    Log("*Pero no eres un experto, los beneficios son menores*");
                    Log("*Attack +2*");
                    Log("*Defense +0*");
                    Log("*Skill -2*");
                    save.close();
                    data.currentWeapon = EWeapon::hammer;
                    data.progress = 8;
                    data.attack += 2;
                    data.defense += 0;
                    data.skill -= 2;
                    data.attackaccuracy1 = 80;
                    data.attack1power = data.attack;
                    data.attackaccuracy1 = 70;
                    data.attack2power = data.attack1power + 6;
                    save.open("data.sav", std::ios::out);
                    if (save.is_open())
                    {
                        //dumpear la estructura data
                        save.seekp(0, std::ios::beg);
                        save.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
            }
            Log("*Despues del cambio escuchas la voz de GlabGlamer.*");
            Log("GlabGlamer: Tonto tonto que solo sabe pelear, ahora ni eso podras lograr.");
            Log("*Escuchas una risa alocada y luego se hace silencio.*");
        }
    }
    else if (answer == "2")
    {
        Log("GlabGlamer: Entiendo! mi prensencia es intimidante!");
        Log("GlabGlamer: El que no arriesga no gana, pero tampoco pierde!");
        Log("GlabGlamer: Ve con bien aventurero y no llores! Cuando los hombres se despiden no deben llorar");
        Log("*GlabGlamer llora rios de lagrimas mientras se despide*");
        save.close();
        data.progress = 8;
        save.open("data.sav", std::ios::out);
        if (save.is_open())
        {
            //dumpear la estructura data
            save.seekp(0, std::ios::beg);
            save.write((const char*)&data, sizeof(SGameData));
        }
        else
        {
            Log("no se pudo crear el archivo");
        }
    }
    else if (answer == "3")
    {
        Log("GlabGlamer: Supongo que ya no puedo llamarme GlabGlamer");

        Log("*Como contestas?*");
        Log("1.'Respondere tu acertijo oh Gran NoGlabGlamer'");
        Log("2.'Estoy muy asustado para contestar oh maginifico NoGlabGlamer!'");
        Log("3. *Ataca*");
        Log("Cualquier otra tecla. *vete sin decir nada.*");

        std::cin >> answer3;

        if (answer3 == "1") 
        {
            Log("NoGlabGlamer: Aprecio tu velentia! Muy bien escucha las palabras de NoGlabGlamer");
            Log("En la sala de fuegos eternos. una salamandra, un dragon y un fenix. Discutian acaloradamente sobre quien de ellos poseia el fuego mas caliente.");
            Log("La salamandra dijo: 'Mi fuego nace de la alquimia, de mi se escriben cuentos de transformacion. Mi cuerpo siempre esta caliente, incluso en el invierno mas frio.'");
            Log("El dragon rugio: 'Mi aliento escupe fuego, capaz de derretir acero. Mis llamas pueden arrasar montañas y reducir ciudades enteras a cenizas.'");
            Log("El fenix entonces replicó: 'Naci de las cenizas, mi cuerpo es una llama viviente. Cuando muero, exploto en un incendio tan intenso que quema hasta a la muerte'");
            Log("NoGlabGlamer quien escuchaba les dijo: 'Todos tienen un buen punto, diria yo que el fuego mas caliente le pertenece aquel que caliente el invierno, pueda derretirlo todo y sus llamas sean parte del ciclo de la vida y la muerte.");
            Log("Las tres criaturas lo pensaron y asintieron aceptando mi sabiduría, dejando la sala fuimos a comer unas rocas de lava");
            Log("pero la pregunta para ti se queda, que ente tiene el fuego mas caliente?");

            std::cin >> answer3;

            if (answer3 == "sol" || answer3 == "SOL" || answer3 == "Sol")
            {
                Log("NoGlabGlamer: Correcto! el fuego mas caliente viene del sol, osea en su superficie no los rayos suelen ser hasta cuatro veces mas calientes pero eso a nadie le importa.");
                Log("NoGlabGlamer: Tu subiduria ha impresionado a NoGlabGlamer y por ello tienes mi bendicion");
                Log("*Todos tus stats suben dramaticamente*");
                Log("*Hp +5*");
                Log("*Attack +2*");
                Log("*defense +2*");
                Log("*Skill +2*");
                Log("NoGlabGlamer: Buena suerte aventurero!");
                save.close();
                data.progress = 8;
                data.attack += 2;
                data.defense += 2;
                data.skill += 2;
                data.maxhp += 5;
                data.hp = data.maxhp;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else if (answer3 == "NoGlabGlamer")
            {
                Log("NoGlabGlamer: NoGlabGlamer? dijiste NoGlabGlamer?! Eso es... CORRECTO!!!");
                Log("NoGlabGlamer: NoGlabGlamer es la respuesta a todas las cosas!!! Toma tu premio");
                Log("*Todos tus stats suben");
                Log("*Hp +2*");
                Log("*Attack +1*");
                Log("*defense +1*");
                Log("*Skill +1*");
                Log("NoGlabGlamer: La fuerza de NoGlabGlamer esta contigo!");
                save.close();
                data.progress = 8;
                data.attack += 1;
                data.defense += 1;
                data.skill += 1;
                data.maxhp += 2;
                data.hp = data.maxhp;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else
            {
                Log("NoGlabGlamer: Oh ho ho! eso es... INCORRECTO");
                Log("NoGlabGlamer: Toma esto perdedor");
                Log("*NoGlabGlamer te dispara un rayo y desaparece, por un segundo no entiendes que paso pero luego miras tu arma*");
                std::cout << "Tu " << weaponToString(data.currentWeapon) << "esta brillando \n";

                std::random_device rd;

                // Crea un objeto de distribución para cada conjunto de números
                std::vector<int> list1 = { 2, 3, 4 };
                std::vector<int> list2 = { 1, 3, 4 };
                std::vector<int> list3 = { 1, 2, 4 };
                std::vector<int> list4 = { 1, 2, 3 };

                if (data.currentWeapon = EWeapon::sword)
                {
                    int random1 = list1[rd() % list1.size()];

                    if (random1 == 2)
                    {
                        Log("Tu espada y escudo cambian a una lanza");
                        Log("*pierdes los beneficios de tus espada*");
                        Log("*Attack -2*");
                        Log("*Defense -2*");
                        Log("*Obtienes los beneficios de la lanza*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense +0*");
                        Log("*Skill +1*");
                        save.close();
                        data.currentWeapon = EWeapon::lance;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense += 0;
                        data.skill += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 75;
                        data.attack2power = data.attack1power + 4;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random1 == 3)
                    {
                        Log("Tu espada y escudo cambian a un martillo");
                        Log("*pierdes los beneficios de tus espada*");
                        Log("*Attack -2*");
                        Log("*Defense -2*");
                        Log("*Obtienes los beneficios del martillo*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +2*");
                        Log("*Defense +0*");
                        Log("*Skill -2*");
                        save.close();
                        data.currentWeapon = EWeapon::hammer;
                        data.progress = 8;
                        data.attack += 2;
                        data.defense += 0;
                        data.skill -= 2;
                        data.attackaccuracy1 = 80;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 70;
                        data.attack2power = data.attack1power + 6;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random1 == 4)
                    {
                        Log("Tu espada y escudo cambian a un arco y flecha");
                        Log("*pierdes los beneficios de tus espada*");
                        Log("*Attack -2*");
                        Log("*Defense -2*");
                        Log("*Obtienes los beneficios del arco y flecha*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense -2*");
                        Log("*Skill +1*");
                        save.close();
                        data.currentWeapon = EWeapon::bow;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense -= 2;
                        data.skill += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 75;
                        data.attack2power = data.attack1power + 5;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                }
                else if (data.currentWeapon = EWeapon::lance)
                {
                    int random2 = list2[rd() % list2.size()];

                    if (random2 == 1)
                    {
                        Log("Tu lanza cambian a una espada y un escudo");
                        Log("*pierdes los beneficios de tus lanza*");
                        Log("*Attack -2*");
                        Log("*Defense -1*");
                        Log("*Skill -1*");
                        Log("*Obtienes los beneficios de la espada y el escudo*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense +1*");
                        save.close();
                        data.currentWeapon = EWeapon::sword;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 85;
                        data.attack2power = data.attack1power + 2;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random2 == 3)
                    {
                        Log("Tu lanza cambian a un martillo");
                        Log("*pierdes los beneficios de tus lanza*");
                        Log("*Attack -2*");
                        Log("*Defense -1*");
                        Log("*Skill -1*");
                        Log("*Obtienes los beneficios del martillo*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +2*");
                        Log("*Defense +0*");
                        Log("*Skill -2*");
                        save.close();
                        data.currentWeapon = EWeapon::hammer;
                        data.progress = 8;
                        data.attack += 2;
                        data.defense += 0;
                        data.skill -= 2;
                        data.attackaccuracy1 = 80;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 70;
                        data.attack2power = data.attack1power + 6;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random2 == 4)
                    {
                        Log("Tu lanza cambian a un arco y flecha");
                        Log("*pierdes los beneficios de tus lanza*");
                        Log("*Attack -2*");
                        Log("*Defense -1*");
                        Log("*Skill -1*");
                        Log("*Obtienes los beneficios del arco y flecha*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense -2*");
                        Log("*Skill +1*");
                        save.close();
                        data.currentWeapon = EWeapon::bow;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense -= 2;
                        data.skill += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 75;
                        data.attack2power = data.attack1power + 5;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                }
                else if (data.currentWeapon = EWeapon::hammer)
                {
                    std::vector<int> list3 = { 1, 2, 4 };

                    int random3 = list3[rd() % list3.size()];

                    if (random3 == 1)
                    {
                        Log("Tu Martillo cambian a una espada y un escudo");
                        Log("*pierdes los beneficios de tus martillo*");
                        Log("*Attack -3*");
                        Log("*Defense -1*");
                        Log("*Skill +2*");
                        Log("*Obtienes los beneficios de la espada y el escudo*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense +1*");
                        save.close();
                        data.currentWeapon = EWeapon::sword;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 85;
                        data.attack2power = data.attack1power + 2;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random3 == 2)
                    {
                        Log("Tu marillo cambian a un lanza");
                        Log("*pierdes los beneficios de tus martillo*");
                        Log("*Attack -3*");
                        Log("*Defense -1*");
                        Log("*Skill +2*");
                        Log("*Obtienes los beneficios del lanza*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense +0*");
                        Log("*Skill +1*");
                        save.close();
                        data.currentWeapon = EWeapon::lance;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense += 0;
                        data.skill += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 75;
                        data.attack2power = data.attack1power + 4;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random3 == 4)
                    {
                        Log("Tu martillo cambian a un arco y flecha");
                        Log("*pierdes los beneficios de tus martillo*");
                        Log("*Attack -3*");
                        Log("*Defense -1*");
                        Log("*Skill +2*");
                        Log("*Obtienes los beneficios del arco y flecha*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense -2*");
                        Log("*Skill +1*");
                        save.close();
                        data.currentWeapon = EWeapon::bow;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense -= 2;
                        data.skill += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 75;
                        data.attack2power = data.attack1power + 5;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                }
                else if (data.currentWeapon = EWeapon::bow)
                {
                    std::vector<int> list4 = { 1, 2, 3 };

                    int random4 = list4[rd() % list4.size()];

                    if (random4 == 1)
                    {
                        Log("Tu arco y flecha cambian a una espada y un escudo");
                        Log("*pierdes los beneficios de tu arco y flecha*");
                        Log("*Attack -2*");
                        Log("*Defense +2*");
                        Log("*Skill -2*");
                        Log("*Obtienes los beneficios de la espada y el escudo*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense +1*");
                        save.close();
                        data.currentWeapon = EWeapon::sword;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 85;
                        data.attack2power = data.attack1power + 2;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random4 == 2)
                    {
                        Log("Tu arco y flecha cambian a un lanza");
                        Log("*pierdes los beneficios de tu arco y flecha*");
                        Log("*Attack -2*");
                        Log("*Defense +2*");
                        Log("*Skill -2*");
                        Log("*Obtienes los beneficios del lanza*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +1*");
                        Log("*Defense +0*");
                        Log("*Skill +1*");
                        save.close();
                        data.currentWeapon = EWeapon::lance;
                        data.progress = 8;
                        data.attack += 1;
                        data.defense += 0;
                        data.skill += 1;
                        data.attackaccuracy1 = 90;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 75;
                        data.attack2power = data.attack1power + 4;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                    else if (random4 == 3)
                    {
                        Log("Tu arco y flecha cambian a martillo");
                        Log("*pierdes los beneficios de tus martillo*");
                        Log("*Attack -2*");
                        Log("*Defense +2*");
                        Log("*Skill -2*");
                        Log("*Obtienes los beneficios del martillo*");
                        Log("*Pero no eres un experto, los beneficios son menores*");
                        Log("*Attack +2*");
                        Log("*Defense +0*");
                        Log("*Skill -2*");
                        save.close();
                        data.currentWeapon = EWeapon::hammer;
                        data.progress = 8;
                        data.attack += 2;
                        data.defense += 0;
                        data.skill -= 2;
                        data.attackaccuracy1 = 80;
                        data.attack1power = data.attack;
                        data.attackaccuracy1 = 70;
                        data.attack2power = data.attack1power + 6;
                        save.open("data.sav", std::ios::out);
                        if (save.is_open())
                        {
                            //dumpear la estructura data
                            save.seekp(0, std::ios::beg);
                            save.write((const char*)&data, sizeof(SGameData));
                        }
                        else
                        {
                            Log("no se pudo crear el archivo");
                        }
                    }
                }
                Log("*Despues del cambio escuchas la voz de NoGlabGlamer.*");
                Log("NoGlabGlamer: Tonto tonto que solo sabe pelear, ahora ni eso podras lograr.");
                Log("*Escuchas una risa alocada y luego se hace silencio.*");
            }
        }
        else if (answer2 == "2")
        {
            Log("NoGlabGlamer: Entiendo! mi prensencia es intimidante!");
            Log("NoGlabGlamer: El que no arriesga no gana, pero tampoco pierde!");
            Log("NoGlabGlamer: Ve con bien aventurero y no llores! Cuando los hombres se despiden no deben llorar");
            Log("*NoGlabGlamer llora rios de lagrimas mientras se despide*");
            save.close();
            data.progress = 8;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (answer2 == "3")
        {
            if (data.currentWeapon = EWeapon::sword)
            {
                Log("*En un fluido movimiento y antes de que el NoGlabGlamer pueda reacionar usas tu espada para decapitarlo");
                Log("*Su pequeña cabeza cae de sus hombros y rueda en el piso*");
                Log("*Obtienes un punto de Skill * ");
                Log("*Te propones a olvidar que esto jamas paso*");
                save.close();
                data.enemysKilled += 1;
                data.progress = 8;
                data.skill += 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else if (data.currentWeapon = EWeapon::lance)
            {
                Log("*Rapido como una serpiente usas tu lanza para atravesar el pequeño cuerpo de NoGlabGlamer");
                Log("*Tu lanza lo levanta varios metros arriba del piso, puedes ver como la vida abandona sus ojos*");
                Log("*Obtienes un punto de attack * ");
                Log("*Te propones a olvidar que esto jamas paso*");
                save.close();
                data.enemysKilled += 1;
                data.progress = 8;
                data.attack += 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else if (data.currentWeapon = EWeapon::hammer)
            {
                Log("*Lanzas todo tu cuerpo asi atras preparando tu gran martillo y en un segundo usas toda tu fuerza y su peso para atacar*");
                Log("*NoGlabGlamer apenas tiempo de gritar antes de que se escuche el sonido de todos sus huesos rompiendose*");
                Log("*De el ahora solo queda un puere de sangre y organos*");
                Log("*Obtienes un punto de attack * ");
                Log("*Te propones a olvidar que esto jamas paso*");
                save.close();
                data.enemysKilled += 1;
                data.progress = 8;
                data.attack += 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
            else if (data.currentWeapon = EWeapon::bow)
            {
                Log("*De un segundo a otro cargas una flecha en tu arco GlabGlamel dice algo pero no lo escuchas solo sueltas tu flecha*");
                Log("*La flecha le da en el pecho y la fuerza de esta hace que su pequeño cuerpo vuele varios metros hasta estrellarse con un arbol*");
                Log("*ahi la flecha se encaja y su pequeño cuerpo queda colgando de este.*");
                Log("*Obtienes un punto de Skill * ");
                Log("*Te propones a olvidar que esto jamas paso*");
                save.close();
                data.enemysKilled += 1;
                data.progress = 8;
                data.skill += 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
            }
        }
        else {
            Log("*Sin decir otra plabra continuas con tu camino*");
            Log("*NoGlabGlamer tampoco dice nada solo mira como te vas en silencio*");
            Log("*Esto es muy incomodo*");
            Log("*Decides acelerar el paso*");
        }
    }
    else if (answer == "4")
    {
        if (data.currentWeapon = EWeapon::sword) 
        {
            Log("*En un fluido movimiento y antes de que el NoGlabGlamer pueda reacionar usas tu espada para decapitarlo");
            Log("*Su pequeña cabeza cae de sus hombros y rueda en el piso*");
            Log("*Obtienes un punto de Skill * ");
            Log("*Te propones a olvidar que esto jamas paso*");
            save.close();
            data.enemysKilled += 1;
            data.progress = 8;
            data.skill += 1;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (data.currentWeapon = EWeapon::lance) 
        {
            Log("*Rapido como una serpiente usas tu lanza para atravesar el pequeño cuerpo de NoGlabGlamer");
            Log("*Tu lanza lo levanta varios metros arriba del piso, puedes ver como la vida abandona sus ojos*");
            Log("*Obtienes un punto de attack * ");
            Log("*Te propones a olvidar que esto jamas paso*");
            save.close();
            data.enemysKilled += 1;
            data.progress = 8;
            data.attack += 1;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (data.currentWeapon = EWeapon::hammer) 
        {
            Log("*Lanzas todo tu cuerpo asi atras preparando tu gran martillo y en un segundo usas toda tu fuerza y su peso para atacar*");
            Log("*NoGlabGlamer apenas tiempo de gritar antes de que se escuche el sonido de todos sus huesos rompiendose*");
            Log("*De el ahora solo queda un puere de sangre y organos*");
            Log("*Obtienes un punto de attack * ");
            Log("*Te propones a olvidar que esto jamas paso*");
            save.close();
            data.enemysKilled += 1;
            data.progress = 8;
            data.attack += 1;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (data.currentWeapon = EWeapon::bow) 
        {
            Log("*De un segundo a otro cargas una flecha en tu arco GlabGlamel dice algo pero no lo escuchas solo sueltas tu flecha*");
            Log("*La flecha le da en el pecho y la fuerza de esta hace que su pequeño cuerpo vuele varios metros hasta estrellarse con un arbol*");
            Log("*ahi la flecha se encaja y su pequeño cuerpo queda colgando de este.*");
            Log("*Obtienes un punto de Skill * ");
            Log("*Te propones a olvidar que esto jamas paso*");
            save.close();
            data.enemysKilled += 1;
            data.progress = 8;
            data.skill += 1;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
    }
    else {
        Log("*Sin decir ni una plabra continuas con tu camino*");
        Log("*GlabGlamer tampoco dice nada solo mira como te vas en silencio*");
        Log("*Esto es muy incomodo*");
        Log("*Decides acelerar el paso*");
    }
    Log(" *Continuas por el sendero del bosque* ");

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> answer;

        if (answer == "C" || answer == "c")
        {
            Log("Continuando");
        }
        else if (answer == "Q" || answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (answer != "q" && answer != "Q" && answer != "c" && answer != "C");
}

void DryadEncounter(SGameData& data, std::fstream& save) 
{
    Enemies Dryad1;
    Enemies Dryad2;
    Dryad1.namea = "Carnivorous Male Dryad";
    Dryad1.hp = 30;
    Dryad1.attack = 10;
    Dryad1.defense = 2;
    Dryad1.skill = 4;
    Dryad1.attack1power = Dryad1.attack;
    Dryad1.attackaccuracy1 = 100;
    Dryad1.attack2power = Dryad1.attack + 5;
    Dryad1.attackaccuracy2 = 80;

    Dryad2.namea = "Carnivorous Female Dryad";
    Dryad2.hp = 35;
    Dryad2.attack = 9;
    Dryad2.defense = 2;
    Dryad2.skill = 4;
    Dryad2.attack1power = Dryad2.attack;
    Dryad2.attackaccuracy1 = 100;
    Dryad2.attack2power = Dryad2.attack + 5;
    Dryad2.attackaccuracy2 = 80;
    NLog(data, " continua su camino por el bosque y entra a una pradera llena de hermosas flores.");
    Log("Una placentera brisa pasa por el aire.");
    NLog(data, "Tiene que pelear contra la tentacion de acostarse junto a las flores y dormir.");
    Log("El ambiente del la pradera es realmente placentero");
    LogN("De Pronto el aroma mas delicioso golpea a ", data);
    Log("Es fresco y dulce dejando un ligero cosquilleo en la nariz");
    NLog(data, "no puede dejar de pensar en el, el aroma parece habarse apoderado de su cerebro");
    LogN("Sin pensarlo", data);
    Log("emepezo a seguir el aroma a su origen, donde encontro una rosa apartada de las demas flores");
    NLog(data, "agacho la cabeza para poder oler la rosa de mas cerca, el aroma era mucho mas dulce e intenso aqui");
    NLog(data, " No tiene idea por que lo hizo, quizas fue instinto.");
    Log("Pero, de un momento a otro dejo de oler el aroma y dio un salto hacia atras.");
    Log("Cuando lo hizo se dio cuenta que la rosa se habia agrandado era mas grande que su cabeza");
    Log("Peor aun, los petalos tenian filos dientes y se estaban cerrando justo donde estaba si cabeza hace unos segundos.");
    Log("Drayd roja: Amor. El humano se quito");
    Log("*una hermosa mujer salio de entre los arboles, se veia como si una rosa hubiera tomado forma humana*");
    Log("*Seguida de ella vino salio un hombre, era mas tosco que la mujer, como un sauce humano*");
    Log("Drayd cafe: Por que te moviste humano? la mordida de mi amada es un experiencia unica.");
    Log("Dryad cafe: Sus jugos gastricos son un poderoso alucinojeno, tus ultimos momentos de vida hubieran sido extasis");
    Log("Drayd roja: Quizas prefiera el dolor?");
    Log("*dos vainas llenas de espinas salieron de las manos de la Dryad roja*");
    Log("Drayad cafe: Si es asi, podemos cumplir su deseo");
    std::cout << data.name << " *prepara su arma*";

    std::string Answer;
    do
    {
        std::cout << data.name << " Tiene " << data.hp << "\n";
        Log("*Elige un ataque*");
        Log("1. Ataque Normal");
        Log("2. Ataque Fuerte");

        std::cin >> Answer;

        if (Answer == "1")
        {
            std::string Target;

            {
                Log("*Elige un objetivo*");
                Log("1. Carnivorous Male Dryad");
                Log("2. Carnivorous Female Dryad");
                std::cin >> Target;

                if (Target == "1" && Dryad1.hp > 0) {
                    Dryad1.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Dryad1.skill, Dryad1.defense, Dryad1.hp, data, Dryad1);
                    if (Dryad1.hp <= 0) {
                        Dryad1.hp = 0;
                        Log("Carnivorous Male Dryad ha sido derrotado.");

                        if (Dryad2.hp != 0) 
                        {
                            Log("Dryad roja: Amor? Amor?!");
                            Log("*La Dryad roja deja salir un grito lleno de ira*");
                            Log("Dryad roja: TE VOY A DIGIRIR VOY A DEJARTE VIVO EN MI ESTOMAGO POR MESES DEJARE QUE TE DERITAS VIVO!");
                            Log("*La ira de la Dryad roja modifica sus stats*");
                            Log("*+Hp*");
                            Log("*+Defense*");
                            Log("*-Skill*");
                            Dryad2.defense += 4;
                            Dryad2.hp += 20;
                            Dryad2.skill -= 2;
                        }
                    }
                }
                else if (Target == "2" && Dryad2.hp > 0) {
                    Dryad2.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Dryad2.skill, Dryad2.defense, Dryad2.hp, data, Dryad2);
                    if (Dryad2.hp <= 0) {
                        Dryad2.hp = 0;
                        Log("Carnivorous Female Dryad ha sido derrotada.");
                        if (Dryad1.hp != 0) 
                        {
                            Log("Dryad cafe: No! NOOO!");
                            Log("*Raices salen de la tierra alrededor de el Dryad*");
                            Log("Dryad cafe: Te voy a matar! te voy a matar! te voy a matar...");
                            Log("*La ira del Dryad cafe modifica sus stats*");
                            Log("*+Attack*");
                            Log("*+Defense*");
                            Log("*-Skill*");
                            Dryad2.attack += 4;
                            Dryad2.defense += 2;
                            Dryad2.skill -= 2;
                        }
                    }
                }
                else {
                    Log("El objetivo ya ha sido derrotado o el número introducido es incorrecto, elige otro objetivo.");
                }
            }
        }
        else if (Answer == "2")
        {
            std::string Target;
            {
                Log("*Elige un objetivo*");
                Log("1. Carnivorous Male Dryad");
                Log("2. Carnivorous Female Dryad");
                std::cin >> Target;

                if (Target == "1" && Dryad1.hp > 0) {
                    Dryad1.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Dryad1.skill, Dryad1.defense, Dryad1.hp, data, Dryad1);
                    if (Dryad1.hp <= 0) {
                        Dryad1.hp = 0;
                        Log("Carnivorous Male Dryad ha sido derrotado.");
                    }
                }
                else if (Target == "2" && Dryad2.hp > 0) {
                    Dryad2.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Dryad2.skill, Dryad2.defense, Dryad2.hp, data, Dryad2);
                    if (Dryad2.hp <= 0) {
                        Dryad2.hp = 0;
                        Log("Carnivorous Female Dryad ha sido derrotada.");
                    }
                }
                else {
                    Log("El objetivo ya ha sido derrotado o el número introducido es incorrecto, elige otro objetivo.");
                }
            }
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
            continue;
        }

        // Los goblins atacan
        if (data.hp > 0 && (Dryad1.hp > 0 || Dryad2.hp > 0))
        {
            srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios

            if (Dryad1.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Dryad1.attack1power, Dryad1.attackaccuracy1, data.skill, data.defense, data.hp, data, Dryad1);
                }
                else {
                    data.hp = calculateDamage(Dryad1.attack2power, Dryad1.attackaccuracy2, data.skill, data.defense, data.hp, data, Dryad1);
                }
            }

            if (Dryad2.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Dryad2.attack1power, Dryad2.attackaccuracy1, data.skill, data.defense, data.hp, data, Dryad2);
                }
                else {
                    data.hp = calculateDamage(Dryad2.attack2power, Dryad2.attackaccuracy2, data.skill, data.defense, data.hp, data, Dryad2);
                }
            }
            if (data.hp <= 0) {
                save.close();
                data.currentWeapon = EWeapon::none;
                data.enemysKilled = 0;
                data.progress = 1;
                data.path = 1;
                data.hp = 50;
                data.maxhp = 50;
                data.attack = 6;
                data.defense = 5;
                data.skill = 2;
                data.attackaccuracy1 = 100;
                data.attack1power = data.attack;
                data.attackaccuracy2 = 100;
                data.attack2power = data.attack + 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
                Log("Has muerto");
                Log("No pudiste probar que tenias lo necesario para ser un heroe");
                Log("Despues de un tiempo, Mel se llevo tus cosas utiles y quemo las demas.");
                Log("Fin.");
                save.close();
                exit(0);
            }
        }

    } while (data.hp > 0 && (Dryad1.hp > 0 || Dryad2.hp > 0));

    Log("Has derotado a los mounstros.");
    Log("*Despues de la batalla tus stats suben!*");
    Log("*Defense +2*");
    Log("*Skill +1*");
    Log("*La rosa se marchita, pero puedes sentir lo ultimo de su poder entrando a ti*");
    Log("*HP +40*");
    save.close();
    data.enemysKilled += 2;
    data.progress = 8;
    data.defense += 2;
    data.skill += 1;
    data.hp = data.maxhp;
    save.open("data.sav", std::ios::out);
    if (save.is_open())
    {
        //dumpear la estructura data
        save.seekp(0, std::ios::beg);
        save.write((const char*)&data, sizeof(SGameData));
    }
    else
    {
        Log("no se pudo crear el archivo");
    }

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void Stage3(SGameData& data, std::fstream& save)
{
    Enemies Manticore;
    Manticore.namea = "Newbie Killer Manticore";
    Manticore.hp = 65;
    Manticore.attack = 12;
    Manticore.defense = 4;
    Manticore.skill = 6;
    Manticore.attack1power = Manticore.attack;
    Manticore.attackaccuracy1 = 100;
    Manticore.attack2power = Manticore.attack + 15;
    Manticore.attackaccuracy2 = 50;
    NLog(data, " Camina por mucho tiempo, el cansancio esta empezando a afectarle");
    Log("Finalmete al final de un moton de arboles se ve una luz");
    NLog(data, " Corre hacia la luz y encunetra una seccion libre de arboles y en el centro un pedestal con la pocima encima.");
    NLog(data,  "Lleno de emocion se acerco hacia la pocion pero un rugido hizo que se detuviera.");
    Log("De los arboles salio un leon blanco.");
    std::cout << " en ese momento " << data.name << " Solo pudo pensar " << " *Que hace un Leon en el bosque* ";
    Log("Cuando el miedo de la primera impresion paso, Se dio cuenta de que este no era un leon normal");
    Log("Tenia una cola de escorpion y alas como ave.");
    Log("No es solo un Leon, es el asesino de novatos por excelencia una Manticora!");
    NLog(data, "siente la adrenalina en todo su cuerpo, es el momento de la verdad.");
    std::string Answer;
    do
    {
        Log("*Tu cuerpo esta listo para romper sus limites decide que stat aumentar.*");
        Log("1. *Attack*");
        Log("2. *Defense*");
        Log("3. *Skill*");
        Log("4. *HP*");
        std::cin >> Answer;

        if (Answer == "1") 
        {
            Log("*Attack +3*");
            data.attack += 3;
        }
        else if (Answer == "2") 
        {
            Log("*Defense +3*");
            data.defense += 3;
        }
        else if (Answer == "3")
        {
            Log("*Skill +3*");
            data.skill += 3;
        }
        else if (Answer == "4")
        {
            Log("*HP +10*");
            data.maxhp += 10;
            data.hp = data.maxhp;
        }
        else 
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "1" && Answer != "2" && Answer != "3" && Answer != "4");
    do
    {
        std::cout << data.name << " Tiene " << data.hp << "\n";
        Log("*Elige un ataque*");
        Log("1. Ataque Normal");
        Log("2. Ataque Fuerte");

        std::cin >> Answer;

        if (Answer == "1") {
            Manticore.hp = calculateDamageP(data.attack1power, data.attackaccuracy1, Manticore.skill, Manticore.defense, Manticore.hp, data, Manticore);
            if (Manticore.hp <= 0) {
                Manticore.hp = 0;
                Log("Newbie Killer Manticore.");
            }
        }

        else if (Answer == "2"){
             Manticore.hp = calculateDamageP(data.attack2power, data.attackaccuracy2, Manticore.skill, Manticore.defense, Manticore.hp, data, Manticore);
             if (Manticore.hp <= 0) {
                 Manticore.hp = 0;
                 Log("Newbie Killer Manticore.");
             }
           }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
            continue;
        }

        
        if (data.hp > 0 && (Manticore.hp > 0))
        {
            srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios

            if (Manticore.hp > 0) {
                int selectedAttack = rand() % 2; // Genera 0 o 1
                if (selectedAttack == 0) {
                    data.hp = calculateDamage(Manticore.attack1power, Manticore.attackaccuracy1, data.skill, data.defense, data.hp, data, Manticore);
                }
                else {
                    data.hp = calculateDamage(Manticore.attack2power, Manticore.attackaccuracy2, data.skill, data.defense, data.hp, data, Manticore);
                }
            }
            if (data.hp <= 0) {
                save.close();
                data.currentWeapon = EWeapon::none;
                data.enemysKilled = 0;
                data.progress = 1;
                data.path = 1;
                data.hp = 50;
                data.maxhp = 50;
                data.attack = 6;
                data.defense = 5;
                data.skill = 2;
                data.attackaccuracy1 = 100;
                data.attack1power = data.attack;
                data.attackaccuracy2 = 100;
                data.attack2power = data.attack + 1;
                save.open("data.sav", std::ios::out);
                if (save.is_open())
                {
                    //dumpear la estructura data
                    save.seekp(0, std::ios::beg);
                    save.write((const char*)&data, sizeof(SGameData));
                }
                else
                {
                    Log("no se pudo crear el archivo");
                }
                Log("Has muerto");
                Log("No pudiste probar que tenias lo necesario para ser un heroe");
                Log("Despues de un tiempo, Mel se llevo tus cosas utiles y quemo las demas.");
                Log("Fin.");
                save.close();
                exit(0);
            }
        }

    } while (data.hp > 0 && Manticore.hp > 0);

    Log("*Has derotado a la manticora*");
    Log("*Despues de la batalla tus stats suben de forma critica!*");
    Log("*Attack +10*");
    Log("*Defense +10*");
    Log("*Skill +10*");
    Log("*Max Hp +20*");
    save.close();
    data.enemysKilled += 1;
    data.progress = 9;
    data.attack += 10;
    data.defense += 10;
    data.skill += 9;
    data.maxhp += 20;
    data.hp = data.maxhp;
    save.open("data.sav", std::ios::out);
    if (save.is_open())
    {
        //dumpear la estructura data
        save.seekp(0, std::ios::beg);
        save.write((const char*)&data, sizeof(SGameData));
    }
    else
    {
        Log("no se pudo crear el archivo");
    }

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void Pocion(SGameData& data, std::fstream& save)
{
    Log("*Con un ultimo rugido la manticora cae, antes de que puedas dar el golpe de gracia usa su alas para huir.*");
    Log("*Exhausto caes sobre una de tus rodillas y recuperas tu aliento.*");
    Log("*Tus ojos fijos en tu premio, la pocima en el pedestal.*");
    Log("*Con esfuerzo te levantas y caminas hasta ella. tus dedos se cierran alrededor de la botella*");
    NLog(data, "Obtiene la botella!");
    Log("*Te dispones a regresar truinfal pero una vocesita dentro de ti te detiene.*");
    Log("*Debería beber la pocima? Se supone que me haria mas fuerte mucho mas fuerte...*");
    std::string Answer;
    do
    {
        Log("1. 'No'");
        Log("2. 'Si'");
        std::cin >> Answer;

        if (Answer == "1") 
        {
            save.close();
            data.progress = 10;
            data.path = 1;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else if (Answer == "2") 
        {
            save.close();
            data.progress = 10;
            data.path = 2;
            save.open("data.sav", std::ios::out);
            if (save.is_open())
            {
                //dumpear la estructura data
                save.seekp(0, std::ios::beg);
                save.write((const char*)&data, sizeof(SGameData));
            }
            else
            {
                Log("no se pudo crear el archivo");
            }
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }

    } while (Answer != "1" && Answer != "2");

    Log("Quieres continuar?");
    do
    {
        Log("*Presiona Q para salir y C para continuar");
        std::cin >> Answer;

        if (Answer == "C" || Answer == "c")
        {
            Log("Continuando");
        }
        else if (Answer == "Q" || Answer == "q")
        {
            Log("Salvando.");
            Log("Saliendo del juego");
            exit(0);
        }
        else
        {
            Log("Respuesta no valida, porfavor vuelva a intentar.");
        }
    } while (Answer != "q" && Answer != "Q" && Answer != "c" && Answer != "C");
}

void GodEnding(SGameData& data, std::fstream& save)
{
    Log("Mel ya te habia advertido de esto, quien tome la pocima sin permiso sera marcado como traedor.");
    Log("Y los traedores del gremio de heroes son perseguidos hasta la muerte.");
    Log("Sin importar que tan fuerte te vuelvas no crees poder vencer a todo el gremio.");
    Log("Decides que lo mejor es no beber la pocima.");

    Log("Presiona cualquier tecla mas 'Enter'");
    std::string Answer;
    std::cin >> Answer;

    Log("Regresas por el bosque, en el camino no encuentras ninguna dificultad. Es como si los residentes del bosque supieran de tu victoria!");
    Log("Finalmente te encuentras con Mel");
    Log("Mel: huh. No pense que te volveria a ver.");
    Log("Mel: Supongo que ya no puedo tratarte como un mocoso, ahora somos compañeros de trabajo.");
    Log("Mel: Ven, te invitare una cerveza en la taverna para celebrar. Quizas en el camino pueda enseñarte un hechizo o dos.");
    Log("*Mel nunca habia sido tan amable contigo. La manera en la que te ve a cambiado por completo.*");
    Log("*realmente debes de haberte vuelto un heroe! Y esto es solo el principio*");
    Log("*Propones volverte el heroe mas grande de todos los tiempos!*");
    Log("'Fin!'");

    std::cout << "Stats Finales. ";
    std::cout << data.attack << " Puntos de Ataque " << "\n";
    std::cout << data.defense << " Puntos de Defesa " << "\n";
    std::cout << data.skill << " Puntos de Habilidad " << "\n";
    std::cout << data.maxhp << " Puntos de Vida maximos " << "\n";
    std::cout << "Tu arma fue " << data.currentWeapon << "\n";
    std::cout << "Derrotaste a " << data.enemysKilled << "\n";

    Log("'Gracias por jugar'");
}

void BadEnging(SGameData& data, std::fstream& save)
{
    Log("Por que no? Despues de todo, tu fuiste el que obtuvo. Es tu premio por llegar tan lejos.");
    Log("Si alguien merece este poder eres tu!");
    Log("*Sin pensarlo mas destapas la botella y bebes su contenido!*");
    Log("*El poder que sientes es incomparable*");
    Log("*Todos tus stats se quintuplican*");
    data.attack *= 5;
    data.defense *= 5;
    data.skill *= 5;
    data.maxhp *= 5;

    std::cout << "Ahora tienes. " << data.attack << " Puntos de Ataque " << "\n";
    std::cout << "Ahora tienes. " << data.defense << " Puntos de Defensa " << "\n";
    std::cout << "Ahora tienes. " << data.skill << " Puntos de Habilidad " << "\n";
    std::cout << "Ahora tienes. " << data.maxhp << " Puntos de Vida " << "\n";

    Log("Con tanto poder en tu cuerpo estas seguro que eres invencible!");
    Log("Estas seguro que podras tomar el control del Gremio!");
    Log("Y lo primero que haras sera enseñarle una leccion a mel.");

    Log("Presiona cualquier tecla mas 'Enter'");

    std::string Answer;
    std::cin >> Answer;

    Log("Regresas por el bosque, en el camino no encuentras ninguna dificultad. Los residentes del bosque estaban claramente intimidados por tu poder!");
    Log("Finalmente te encuentras con Mel");
    Log("Mel: huh. No pense que te volveria a ver.");
    Log("Mel: Espera, y la pocima?");
    Log("*Sonries preparando tu arma*");
    Log("Mel: Oh! ya veo, es una lastima claramente tenias potencial, pero parece que no eres muy listo");
    Log("Las palabras de Mel ya no podran intimidarte. Estas listo para ella");
    Log("De hecho las pocion desbloquea un nuevo poder, puedes analizar a Mel y ver su verdadero poder");
    Log("Mel of the purple lighting stats: Puntos de ataque 1331, Puntos de Defensa 1103, Puntos de Habilidad 1512, Puntos de Vida 2123");
    Log("*Tu cara empalidece*");
    Log("Mel: Parece que entiendes el terrible error que cometiste, nene.");
    Log("Mel: La pocima es un desperdicio en una lombriz como tu.");
    Log("Mel: Adios, prometo no extrañarte.");
    Log("*Lo ultimo que ves es un luz morado, probablemente un rayo.*");
    Log("*Mel ato tu cuerpo a tu caballo y te arrastro hasta la ciudad.*");
    Log("*Donde tu cabeza fue puesta en una lanza, una advertencia para los traidores.*");
    Log("*Creo que no debiste haber bebido la pocima.*");
    Log("Fin");

    save.close();
    data.progress = 9;
    data.attack *= 5;
    data.defense *= 5;
    data.skill *= 5;
    data.maxhp += 5;
    save.open("data.sav", std::ios::out);
    if (save.is_open())
    {
        //dumpear la estructura data
        save.seekp(0, std::ios::beg);
        save.write((const char*)&data, sizeof(SGameData));
    }
    else
    {
        Log("no se pudo crear el archivo");
    }
}

int main()
{
    //leer el archivo de savegame
    std::fstream savefile("data.sav", std::ios::in | std::ios::out);

    void (*Proceso)(SGameData&, std::fstream&) = nullptr;

    if (savefile.is_open())
    {
        Log("savefile abierto");


        //leer datos del archivo
        SGameData data;
        savefile.read(data.name, MAXNAMESIZE);
        savefile.read((char*)&data.currentWeapon, 4);
        savefile.read((char*)&data.enemysKilled, 4);
        savefile.read((char*)&data.progress, 4);
        savefile.read((char*)&data.path, 4);
        savefile.read((char*)&data.hp, 4);
        savefile.read((char*)&data.maxhp, 4);
        savefile.read((char*)&data.attack, 4);
        savefile.read((char*)&data.defense, 4);
        savefile.read((char*)&data.skill, 4);
        savefile.read((char*)&data.attackaccuracy1, 4);
        savefile.read((char*)&data.attack1power, 4);
        savefile.read((char*)&data.attackaccuracy2, 4);
        savefile.read((char*)&data.attack2power, 4);
        
        

        std::cout << "hola " << data.name;
        std::cout << " Tu Arma es " << weaponToString(data.currentWeapon) << " y has derrotado a " << data.enemysKilled << " enemigos" << " Tu progeso es " << data.progress;
        Log(" Quieres Usar este Save file? presiona '1' si la respuesta es si '2' si es no");
        
        std::string Answer;
        //es la primera vez que uso un do while holy moly
        
            do
            {
                Log("Quieres usar este archivo de guardado?");
                std::cin >> Answer;


                if (data.progress == 1 && Answer == "1")
                {
                    // Usuario ha decidido usar este archivo de guardado.
                    LogN("Bienvenido", data);
                    Log("Al bosque del inicio!");
                    Log("Estas aqui para demostrar que tienes lo necesario para ser un Heroe!");
                    Log("Vienes con una examinadora del gremio de heroes, ella puede resolver tus dudas.");
                    Log("Buena suerte, persiona cualquier tecla para continuar");

                    std::cin.get();

                    savefile.close();
                    data.progress = 2;
                    savefile.open("data.sav", std::ios::out);
                    if (savefile.is_open())
                    {
                        //dumpear la estructura data
                        savefile.seekp(0, std::ios::beg);
                        savefile.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                    tutorial(data, savefile);
                    WeaponChoice(data, savefile);
                    Stage1(data, savefile);
                    if (data.path == 1)
                        Proceso = &GoblinAttack;
                    else if (data.path == 2)
                        Proceso = &WispAttack;
                    Proceso(data, savefile);
                    Stage2(data, savefile);
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 2 && Answer == "1") 
                {
                    tutorial(data, savefile);
                    WeaponChoice(data, savefile);
                    Stage1(data, savefile);
                    if (data.path == 1)
                        Proceso = &GoblinAttack;
                    else if (data.path == 2)
                        Proceso = &WispAttack;
                    Proceso(data, savefile);
                    Stage2(data, savefile);
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 3 && Answer == "1")
                {
                    WeaponChoice(data, savefile);
                    Stage1(data, savefile);
                    if (data.path == 1)
                        Proceso = &GoblinAttack;
                    else if (data.path == 2)
                        Proceso = &WispAttack;
                    Proceso(data, savefile);
                    Stage2(data, savefile);
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 4 && Answer == "1")
                {
                    Stage1(data, savefile);
                    if (data.path == 1)
                        Proceso = &GoblinAttack;
                    else if (data.path == 2)
                        Proceso = &WispAttack;
                    Proceso(data, savefile);
                    Stage2(data, savefile);
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 5 && Answer == "1")
                {
                    if (data.path == 1)
                        Proceso = &GoblinAttack;
                    else if (data.path == 2)
                        Proceso = &WispAttack;
                    Proceso(data, savefile);

                    Stage2(data, savefile);
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 6 && Answer == "1") 
                {
                    Stage2(data, savefile);
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 7 && Answer == "1")
                {
                    if (data.path == 1)
                        Proceso = &Decision;
                    else if (data.path == 2)
                        Proceso = &DryadEncounter;
                    Proceso(data, savefile);
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 8 && Answer == "1")
                {
                    Stage3(data, savefile);
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 9 && Answer == "1") 
                {
                    Pocion(data, savefile);
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (data.progress == 10 && Answer == "1")
                {
                    if (data.path == 1)
                        Proceso = &GodEnding;
                    else if (data.path == 2)
                        Proceso = &BadEnging;
                    Proceso(data, savefile);
                }
                else if (Answer == "2")
                {
                    savefile.close();
                    Log("Porfavor elige otro nombre");
                    std::cin >> data.name;
                    data.currentWeapon = EWeapon::none;
                    data.enemysKilled = 0;
                    data.progress = 1;
                    data.path = 1;
                    data.hp = 50;
                    data.maxhp = 50;
                    data.attack = 6;
                    data.defense = 5;
                    data.skill = 2;
                    data.attackaccuracy1 = 100;
                    data.attack1power = data.attack;
                    data.attackaccuracy2 = 100;
                    data.attack2power = data.attack + 1;
                    savefile.open("data.sav", std::ios::out);
                    if (savefile.is_open())
                    {
                        //dumpear la estructura data
                        savefile.seekp(0, std::ios::beg);
                        savefile.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else
                {
                    // Respuesta del usuario no reconocida.
                    Log("Respuesta no reconocida. Por favor, responde con 'yes' o 'no'.");
                }
            } while (Answer != "1" && Answer != "2");
    }
    else
    {
        Log("crear savefile vacio e inicial");
        SGameData data;
        Log("Elige tu nombre:");
        std::cin >> data.name;
        data.currentWeapon = EWeapon::none;
        data.enemysKilled = 0;
        data.progress = 1;
        data.path = 1;
        data.hp = 50;
        data.maxhp = 50;
        data.attack = 6;
        data.defense = 5;
        data.skill = 2;
        data.attackaccuracy1 = 100;
        data.attack1power = data.attack;
        data.attackaccuracy2 = 100;
        data.attack2power = data.attack + 1;
        savefile.open("data.sav", std::ios::out);
        if (savefile.is_open())
        {
            //dumpear la estructura data
            savefile.seekp(0, std::ios::beg);
            savefile.write((const char*)&data, sizeof(SGameData));
        }
        else
        {
            Log("no se pudo crear el archivo");
        }

    }

    savefile.close();

    return 0;
}

