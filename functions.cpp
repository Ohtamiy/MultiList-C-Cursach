#include <functions.h>

/* Функцiя iнiцiалiзацiї масиву вказiвникiв */
void**initArr()
{
    void** p = new void*[SIZE_AR_FIRST]; //видiляємо пам`ять пiд масив вказiвникiв, SIZE_AR_FIRST - початковий розмiр масиву
    p = p+2; //переходимо до вказiвника на перший елемент, 2 попереднi є службовими
    ((int*)p)[POS_CNT] = 0; //1-ий службовий вказiвник зберiгає iнформацiю про кiлькiсть вказiвникiв в масивi вказiвникiв
    ((int*)p)[POS_SZ] = SIZE_AR_FIRST; //2-ий службовий вказiвник зберiгає iнформацiю про можливу кiлькiсть вказiвникiв в масивi вказiвникiв
    return p; //повертаємо створений масив
}

/* Функцiя збiльшення розмiру масиву вказiвникiв
 * Отримує вказiвник на масив вказiвникiв */
void extend(void**&rail)
{
    int cnt = ((int*)rail)[POS_CNT]; //отримуємо кiлькiсть вказiвникiв
    int size = ((int*)rail)[POS_SZ]; //отримуємо можливу кiлькiсть вказiвникiв
    size = size + DELTA; //збiльшуємо можливу кiлькiсть вказiвникiв на встановлений розмiр DELTA
    void **p = new void*[size+2]; //видiляємо пам`ять пiд масив вказiвникiв + 2 службовi вказiвники
    ((int*)p)[POS_SZ] = size; //записуємо в iнформацiю в службовi вказiвники
    ((int*)p)[POS_CNT] = cnt;
    for(int i = 0; i < (size - DELTA); i++) //переписуємо iнформацiю зi старого масиву в новий
        p[i+1] = rail[i];
    delete[]rail; //видаляємо старий
    rail = p; //отримуємо новий
}

/* Функцiя додавання покажчика на новий елемент в масив покажчикiв
 * Отримує вказiвник на масив вказiвникiв, вказiвник на новий елемент та позицiю для вставки */
void addToSort(void**&rail, void *pnew, int posAdd)
{
    int cnt = ((int*)rail)[POS_CNT]; //отримуємо кiлькiсть вказiвникiв
    int size = ((int*)rail)[POS_SZ]; //отримуємо можливу кiлькiсть вказiвникiв
    if(cnt == size) //якщо вони спiвпадають, то
        extend(rail); //збiльшуємо розмiру масиву вказiвникiв
    if(posAdd != cnt) //якщо вставляємо не в кiнець масиву
        for(int k = cnt - 1; k >= posAdd; k--) //зсуваємо всi елементи вiд позицiя вставки до кiнця
            rail[k+1] = rail[k]; //праворуч
    rail[posAdd] = pnew; //вставляємо новий елемент
    cnt++; //+1 покажчик в масивi покажчикiв
    ((int*)rail)[POS_CNT] = cnt; //оновлюємо iнформацiю в масивi
}

/* Функцiя пошуку елементу
 * Отримує вказiвник на масив вказiвникiв, ключове поле, позицiю знайденого елемента, змiнну для перевiрки наявностi елемента та вказiвник на функцiю порiвняння елементiв */
void findEl(void** rail, QString key,int &posFndEl, bool &findOK, funcCMP cmpfunc)
{
    findOK = false; //поки що елемент не був знайдений
    if (((int*)rail)[POS_CNT] == 0) //якщо список пустий
    {
        posFndEl = 0; //позицiя для вставки є початком списку
        return;
    }
    int hi, low = 0; //оголошуємо допомiжнi змiннi для границь
    hi = ((int*)rail)[POS_CNT] - 1; //верхня границя є останнiм елементом масиву вказiвникiв
    do{ //цикл
        int middle = (hi + low) / 2; //отримуємо середину списку
        int resultCompare = cmpfunc(rail[middle], key); //порiвнюємо елементи
        if(resultCompare == 0){ //якщо вони однаковi, то
            posFndEl = middle; //це i є знайдена позицiя
            findOK = true; //елемент був знайдений
            return;
        }
        else if(resultCompare == 1) //якщо вони не однаковi, але потрiбний елемент знаходиться лiвiше у списку
            hi = middle - 1; //змiнюємо праву границю
        else low = middle + 1; //якщо потрiбний елемент знаходиться правiше у списку, то змiнюємо лiву границю
    }while(low <= hi); //виконуватися, поки лiва границя менша за праву
    posFndEl = low; //перебрано масив, елемент не знайдено, можливо це i є позицiя для вставки
}

/* Функцiя порiвняння елементв(Мiсто) зi списку 1-ого рiвня
 * Отримує вказiвник на даний елемент та ключове поле */
int cmpTrip(void *p, QString key)
{
    if(atoi(((Trip*)p)->number.toLocal8Bit().constData()) == atoi(key.toLocal8Bit().constData())) //якщо ключове поле i поточний елемент однаковi, то
        return 0; //елемент був знайдений
    else{ //в iншому випадку
        if(atoi(((Trip*)p)->number.toLocal8Bit().constData()) > atoi(key.toLocal8Bit().constData())) //якщо елемент бiльший за ключове поле
            return 1; //шукати треба лiвiше у списку
        else //якщо елемент менший за ключове поле
            return  -1; //шукати треба правiше у списку
    }
}

/* Функцiя порiвняння елементв(Вокзал) зi списку 2-ого рiвня
 * Отримує вказiвник на даний елемент та ключове поле */
int cmpRailSt(void *p, QString key)
{
    if(((RailStation*)p)->name == key) //якщо ключове поле i поточний елемент однаковi, то
        return 0; //елемент був знайдений
    else{ //в iншому випадку
        if(((RailStation*)p)->name > key) //якщо елемент бiльший за ключове поле
            return 1; //шукати треба лiвiше у списку
        else //якщо елемент менший за ключове поле
            return  -1; //шукати треба правiше у списку
    }
}

/* Функцiя порiвняння елементв(Рейс) зi списку 3-ого рiвня
 * Отримує вказiвник на даний елемент та ключове поле */
int cmpCity(void *p, QString key)
{
    if(((City*)p)->city == key) //якщо ключове поле i поточний елемент однаковi, то
        return 0; //елемент був знайдений
    else{ //в iншому випадку
        if(((City*)p)->city > key) //якщо елемент бiльший за ключове поле
            return 1; //шукати треба лiвiше у списку
        else  //якщо елемент менший за ключове поле
            return  -1; //шукати треба правiше у списку
    }
}

/* Функцiя сортування масиву покажчикiв пiсля редагування даних
 * Отримує вказiвник на вiдповiдний рiвень, позицiю змiненого елемента, ключове поле i функцiю порiвняння */
void sortAfterChanging(void **&rail, int posChanged, QString stroka, funcCMP func)
{
    int cnt = ((int*)rail)[POS_CNT]; //отримуємо кiлькiсть вказiвникiв
    while(posChanged != 0 && func(rail[posChanged-1],stroka) == 1){ //цикл: поки не дiйшли до початку масиву i елемент треба вставити лiвiше
        void *temp = rail[posChanged]; //зберiгаємо даний елемент
        rail[posChanged] = rail[posChanged-1]; //на мiсце даного ставимо попереднiй
        rail[posChanged-1] = temp; //на мiсце попереднього ставимо даний
        posChanged--; //переходимо влiво у масивi
    }
    while(posChanged != (cnt - 1) && func(rail[posChanged+1],stroka) == -1){ //цикл: поки не дiйшли до кiнця масиву i елемент треба вставити правiше
        void *temp = rail[posChanged]; //зберiгаємо даний елемент
        rail[posChanged] = rail[posChanged+1]; //на мiсце даного ставимо наступний
        rail[posChanged+1] = temp; //на мiсце наступного ставимо даний
        posChanged++; //переходимо вправо у масивi
    }
}

/* Функцiя видалення елемента(звiльнення пам`ятi)
 * Отримує вказiвник на масив вказiвникiв та позицiю елемента для видалення */
void del(void **&rail, int pos)
{
    int cnt = ((int*)rail)[POS_CNT]; //отримуємо кiлькiсть вказiвникiв в масивi вказiвникiв
    void *wp = rail[pos]; //вказiвник на елемент для видалення
    for(int i = pos; i < cnt-1; i++) //цикл: зсув покажчикiв на мiсце даного покажчика
        rail[i] = rail[i+1]; //лiворуч
    free(wp); //звiльнюємо пам`ять
    ((int*)rail)[POS_CNT] = cnt-1; //оновлюємо iнформацiю в масивi покажчикiв
}

/* Функцiя видалення списку 3-ого рiвня
 * Отримує вказiвник на масив вказiвникiв */
void deletingTrip(void **&rail)
{
    int cnt = ((int*)rail)[POS_CNT]; //отримуємо кiлькiсть вказiвникiв
    for(int i = 0; i < cnt; i++) //цикл: поки не видалимо всi елементи
         del(rail, 0); //звiльняємо пам`ять
}

/* Функцiя видалення списку 2-ого рiвня
 * Отримує вказiвник на масив вказiвникiв */
void deletingRailSt(void **&rail)
{
    int cnt = ((int*)rail)[POS_CNT]; //отримуємо кiлькiсть вказiвникiв
    for(int i = 0; i < cnt; i++){ //цикл: поки не видалимо всi елементи
         deletingTrip(((RailStation*)rail[i])->sublevel); //виклик функцiї видалення для всiх елементiв 3 рiвня - Рейсiв
         del(rail, 0); //звiльняємо пам`ять
    }
}

int countRailStations(void **rail)
{
    int railStations = 0;
    void ** city, ** railSt;
    city = ((Railway*)rail[0])->sublevel;
    int aCity = ((int*)city)[POS_CNT];
    for(int i = 0; i < aCity; i++)
    {
        railSt = ((City*)city[i])->sublevel;
        railStations += ((int*)railSt)[POS_CNT];
    }
    return railStations;
}

/* Функцiя збереження списку у файл
 * Отримує вказiвник на початок списку та шлях файлу */
void saveToFile(void **rail, QString path)
{
    QString pattern = "\"%1\": %2,%3\n"; //iнiцiалiзуємо допомiжнi патерни
    QString pattern1 = "\"%1\": %2,%3,%4\n";
    QString pattern2 = "\"%1\": %2,%3,%4,%5,%6,%7,%8\n";
    QString pattern3 = "\"%1\": %2,%3,%4,%5,%6\n";
    QString tagRail = "R", tagCity = "C", tagRailSt = "V", tagTrip = "T"; //iнiцiалiзуємо допомiжнi заголовки, щоб вiдрiзняти елементи при вiдновленнi

    QFile file(path); //оголошуємо файлову змiнну
    file.open(QIODevice::WriteOnly | QIODevice::Text); //вiдкриваємо текстовий файл на запис

    Railway *railway = ((Railway*)rail[0]); //допомiжна змiнна
    file.write(pattern.arg(tagRail, railway->branch, railway->regions.join(",")).toUtf8()); //записуємо у файл

    int aCity = ((int*)railway->sublevel)[POS_CNT]; //кiлькiсть вказiвникiв на пiдрiвнi
    for(int j = 0; j < aCity; j++){ //цикл: перегляд елементiв
        City *city = ((City*)railway->sublevel[j]); //допомiжна змiнна
        file.write(pattern1.arg(tagCity, city->city, city->region, city->type).toUtf8()); //записуємо у файл
        if(city->sublevel == NULL) continue; //якщо немає пiдрiвня, то переходимо до наступного елемента

        int aRailSt = ((int*)((City*)city)->sublevel)[POS_CNT]; //кiлькiсть вказiвникiв на пiдрiвнi
        for(int k = 0; k < aRailSt; k++){ //цикл: перегляд елементiв
            RailStation *railSt = ((RailStation*)city->sublevel[k]); //допомiжна змiнна
            file.write(pattern2.arg(tagRailSt, railSt->name, QString::number(railSt->pastrafic), QString::number(railSt->rails), QVariant(railSt->service.bathroom).toString(),
                                    QVariant(railSt->service.food).toString(), QVariant(railSt->service.vip).toString(),
                                    QVariant(railSt->service.wifi).toString()).toUtf8()); //записуємо у файл
            if(railSt->sublevel == NULL) continue; //якщо немає пiдрiвня, то переходимо до наступного елемента

            int aTrip = ((int*)((RailStation*)railSt)->sublevel)[POS_CNT]; //кiлькiсть вказiвникiв на пiдрiвнi
            for(int m = 0; m < aTrip; m++){ //цикл: перегляд елементiв
                Trip *trip = ((Trip*)railSt->sublevel[m]); //допомiжна змiнна
                file.write(pattern3.arg(tagTrip, QString::number(trip->duration), trip->from, trip->number, trip->regularity, trip->to).toUtf8()); //записуємо у файл
            }
        }
    }
    file.close(); //закриваємо файл
}

/* Функцiя вiдтворення списку iз файлу
 * Отримує вказiвник на початок списку i шлях фалу */
void retrieveFromFile(void **&rail, QString path)
{
    void **nrail = initArr(); //iнiцiалiзуємо новий список
    QFile file(path); //оголошуємо файлову змiнну
    QString tagRail ="\"R\":", tagCity ="\"C\": ", tagRailSt="\"V\": ", tagTrip ="\"T\": "; //оголошення допомiжних змiнних для запису на вiдповiдний рiвень
    int aRail = 0, aCity = 0, aRailSt = 0, aTrip = 0; //допомiжнi змiннi

    file.open(QIODevice::ReadOnly | QIODevice::Text); //вiдкриваємо текстовий файл на читання

    while(!file.atEnd()){ //цикл: поки не кiнець файлу
        QByteArray bytes = file.readLine(); //зчитуємо
        QString line(bytes); //зчитуємо рядок
        line.remove("\n"); //прибираємо ознаку переходу на наступний рядок
        QStringList item = line.split(","); //iнiцiалiзуємо масив символьних рядкiв iз зчитаного рядка, де елементи роздiленi комою i пробiлом

        if(line.startsWith(tagRail)){ //якщо зчитаний рядок вiдноситься до елемента Деканат
            item[0] = item[0].remove(tagRail); //прибираємо ознаку

            Railway *railway = new Railway; //видiляємо пам'ять
            railway->branch = item[0]; //копiюємо iнформацiйнi поля
            for(int i = 1; i < 25; i++)
                railway->regions << item[i];
            railway->sublevel = initArr(); //iнiцiалiзуємо пiдрiвень

            addToSort(nrail, (void*)railway, aRail++); //додаємо до сортованого списку
            aCity = aRailSt = aTrip = 0; //кiлькiсть елементiв на його пiдрiнях по 0
        }
        else if(line.startsWith(tagCity)){ //якщо зчитаний рядок вiдноситься до елемента Мiсто
            item[0] = item[0].remove(tagCity); //прибираємо ознаку

            City *city = new City; //видiляємо пам'ять
            city->city = item[0]; //копiюємо iнформацiйнi поля
            city->region = item[1];
            city->type = item[2];
            city->sublevel = initArr(); //iнiцiалiзуємо пiдрiвень

            addToSort(((Railway*)nrail[aRail-1])->sublevel, (void*)city, aCity++); //додаємо до сортованого списку
            aRailSt = aTrip = 0; //кiлькiсть елементiв на його пiдрiнях по 0
        }
        else if(line.startsWith(tagRailSt)){ //якщо зчитаний рядок вiдноситься до елемента Вокзал
            item[0] = item[0].remove(tagRailSt); //прибираємо ознаку

            RailStation *railSt = new RailStation; //видiляємо пам'ять
            railSt->name = item[0]; //копiюємо iнформацiйнi поля
            railSt->pastrafic = item[1].toInt();
            railSt->rails = item[2].toInt();
            railSt->service.bathroom = QVariant(item[3]).toBool();
            railSt->service.food = QVariant(item[4]).toBool();
            railSt->service.vip = QVariant(item[5]).toBool();
            railSt->service.wifi = QVariant(item[6]).toBool();
            railSt->sublevel = initArr(); //iнiцiалiзуємо пiдрiвень

            addToSort(((City*)((Railway*)nrail[aRail-1])->sublevel[aCity-1])->sublevel, (void*)railSt, aRailSt++);  //додаємо до сортованого списку
            aTrip = 0; //кiлькiсть елементiв на його пiдрiнi 0
        }
        else if(line.startsWith(tagTrip)){ //якщо зчитаний рядок вiдноситься до елемента Рейс
            item[0] = item[0].remove(tagTrip); //прибираємо ознаку

            Trip *trip = new Trip; //видiляємо пам'ять
            trip->duration = item[0].toFloat();
            trip->from = item[1];
            trip->number = item[2];
            trip->regularity = item[3];
            trip->to = item[4];

            addToSort(((RailStation*)((City*)((Railway*)nrail[aRail-1])->sublevel[aCity-1])->sublevel[aRailSt-1])->sublevel, (void*)trip, aTrip++);  //додаємо до сортованого списку
         }
    }
    file.close(); //закриваємо файл
    rail = nrail; //копiюємо список
}
