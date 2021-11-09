#include <functions.h>

/* �㭪�i� i�i�i��i���i� ��ᨢ� ����i����i� */
void**initArr()
{
    void** p = new void*[SIZE_AR_FIRST]; //���i��� ���`��� �i� ��ᨢ ����i����i�, SIZE_AR_FIRST - ���⪮��� ஧�i� ��ᨢ�
    p = p+2; //���室��� �� ����i����� �� ���訩 �������, 2 ����।�i � �㦡�����
    ((int*)p)[POS_CNT] = 0; //1-�� �㦡���� ����i���� ����i��� i��ଠ�i� �� �i��i��� ����i����i� � ��ᨢi ����i����i�
    ((int*)p)[POS_SZ] = SIZE_AR_FIRST; //2-�� �㦡���� ����i���� ����i��� i��ଠ�i� �� ������� �i��i��� ����i����i� � ��ᨢi ����i����i�
    return p; //������� �⢮७�� ��ᨢ
}

/* �㭪�i� ��i��襭�� ஧�i�� ��ᨢ� ����i����i�
 * ��ਬ�� ����i���� �� ��ᨢ ����i����i� */
void extend(void**&rail)
{
    int cnt = ((int*)rail)[POS_CNT]; //��ਬ�� �i��i��� ����i����i�
    int size = ((int*)rail)[POS_SZ]; //��ਬ�� ������� �i��i��� ����i����i�
    size = size + DELTA; //��i����� ������� �i��i��� ����i����i� �� ��⠭������� ஧�i� DELTA
    void **p = new void*[size+2]; //���i��� ���`��� �i� ��ᨢ ����i����i� + 2 �㦡��i ����i�����
    ((int*)p)[POS_SZ] = size; //������� � i��ଠ�i� � �㦡��i ����i�����
    ((int*)p)[POS_CNT] = cnt;
    for(int i = 0; i < (size - DELTA); i++) //��९���� i��ଠ�i� �i ��ண� ��ᨢ� � �����
        p[i+1] = rail[i];
    delete[]rail; //������� ��਩
    rail = p; //��ਬ�� �����
}

/* �㭪�i� ��������� �����稪� �� ����� ������� � ��ᨢ �����稪i�
 * ��ਬ�� ����i���� �� ��ᨢ ����i����i�, ����i���� �� ����� ������� � �����i� ��� ��⠢�� */
void addToSort(void**&rail, void *pnew, int posAdd)
{
    int cnt = ((int*)rail)[POS_CNT]; //��ਬ�� �i��i��� ����i����i�
    int size = ((int*)rail)[POS_SZ]; //��ਬ�� ������� �i��i��� ����i����i�
    if(cnt == size) //�� ���� �i��������, �
        extend(rail); //��i����� ஧�i�� ��ᨢ� ����i����i�
    if(posAdd != cnt) //�� ��⠢��� �� � �i���� ��ᨢ�
        for(int k = cnt - 1; k >= posAdd; k--) //��㢠� ��i ������� �i� �����i� ��⠢�� �� �i���
            rail[k+1] = rail[k]; //�ࠢ����
    rail[posAdd] = pnew; //��⠢��� ����� �������
    cnt++; //+1 �����稪 � ��ᨢi �����稪i�
    ((int*)rail)[POS_CNT] = cnt; //������� i��ଠ�i� � ��ᨢi
}

/* �㭪�i� ����� ��������
 * ��ਬ�� ����i���� �� ��ᨢ ����i����i�, ���箢� ����, �����i� ���������� �������, ��i��� ��� ��ॢiન �����i ������� � ����i���� �� �㭪�i� ���i��ﭭ� �������i� */
void findEl(void** rail, QString key,int &posFndEl, bool &findOK, funcCMP cmpfunc)
{
    findOK = false; //���� � ������� �� �� ���������
    if (((int*)rail)[POS_CNT] == 0) //�� ᯨ᮪ ���⨩
    {
        posFndEl = 0; //�����i� ��� ��⠢�� � ���⪮� ᯨ��
        return;
    }
    int hi, low = 0; //�������� �����i��i ��i��i ��� �࠭���
    hi = ((int*)rail)[POS_CNT] - 1; //����� �࠭��� � ��⠭�i� ������⮬ ��ᨢ� ����i����i�
    do{ //横�
        int middle = (hi + low) / 2; //��ਬ�� �।��� ᯨ��
        int resultCompare = cmpfunc(rail[middle], key); //���i���� �������
        if(resultCompare == 0){ //�� ���� �������i, �
            posFndEl = middle; //� i � �������� �����i�
            findOK = true; //������� �� ���������
            return;
        }
        else if(resultCompare == 1) //�� ���� �� �������i, ��� ����i���� ������� ���室����� �i�i� � ᯨ��
            hi = middle - 1; //��i��� �ࠢ� �࠭���
        else low = middle + 1; //�� ����i���� ������� ���室����� �ࠢi� � ᯨ��, � ��i��� �i�� �࠭���
    }while(low <= hi); //�����㢠���, ���� �i�� �࠭��� ���� �� �ࠢ�
    posFndEl = low; //��ॡ࠭� ��ᨢ, ������� �� ��������, ������� � i � �����i� ��� ��⠢��
}

/* �㭪�i� ���i��ﭭ� �������(�i��) �i ᯨ�� 1-��� �i���
 * ��ਬ�� ����i���� �� ����� ������� � ���箢� ���� */
int cmpTrip(void *p, QString key)
{
    if(atoi(((Trip*)p)->number.toLocal8Bit().constData()) == atoi(key.toLocal8Bit().constData())) //�� ���箢� ���� i ���筨� ������� �������i, �
        return 0; //������� �� ���������
    else{ //� i�讬� �������
        if(atoi(((Trip*)p)->number.toLocal8Bit().constData()) > atoi(key.toLocal8Bit().constData())) //�� ������� �i��訩 �� ���箢� ����
            return 1; //�㪠� �ॡ� �i�i� � ᯨ��
        else //�� ������� ���訩 �� ���箢� ����
            return  -1; //�㪠� �ॡ� �ࠢi� � ᯨ��
    }
}

/* �㭪�i� ���i��ﭭ� �������(������) �i ᯨ�� 2-��� �i���
 * ��ਬ�� ����i���� �� ����� ������� � ���箢� ���� */
int cmpRailSt(void *p, QString key)
{
    if(((RailStation*)p)->name == key) //�� ���箢� ���� i ���筨� ������� �������i, �
        return 0; //������� �� ���������
    else{ //� i�讬� �������
        if(((RailStation*)p)->name > key) //�� ������� �i��訩 �� ���箢� ����
            return 1; //�㪠� �ॡ� �i�i� � ᯨ��
        else //�� ������� ���訩 �� ���箢� ����
            return  -1; //�㪠� �ॡ� �ࠢi� � ᯨ��
    }
}

/* �㭪�i� ���i��ﭭ� �������(����) �i ᯨ�� 3-��� �i���
 * ��ਬ�� ����i���� �� ����� ������� � ���箢� ���� */
int cmpCity(void *p, QString key)
{
    if(((City*)p)->city == key) //�� ���箢� ���� i ���筨� ������� �������i, �
        return 0; //������� �� ���������
    else{ //� i�讬� �������
        if(((City*)p)->city > key) //�� ������� �i��訩 �� ���箢� ����
            return 1; //�㪠� �ॡ� �i�i� � ᯨ��
        else  //�� ������� ���訩 �� ���箢� ����
            return  -1; //�㪠� �ॡ� �ࠢi� � ᯨ��
    }
}

/* �㭪�i� ���㢠��� ��ᨢ� �����稪i� �i�� ।��㢠��� �����
 * ��ਬ�� ����i���� �� �i����i���� �i����, �����i� ��i������ �������, ���箢� ���� i �㭪�i� ���i��ﭭ� */
void sortAfterChanging(void **&rail, int posChanged, QString stroka, funcCMP func)
{
    int cnt = ((int*)rail)[POS_CNT]; //��ਬ�� �i��i��� ����i����i�
    while(posChanged != 0 && func(rail[posChanged-1],stroka) == 1){ //横�: ���� �� �i�諨 �� ����� ��ᨢ� i ������� �ॡ� ��⠢�� �i�i�
        void *temp = rail[posChanged]; //����i��� ����� �������
        rail[posChanged] = rail[posChanged-1]; //�� �i�� ������ �⠢��� ����।�i�
        rail[posChanged-1] = temp; //�� �i�� ����।�쮣� �⠢��� �����
        posChanged--; //���室��� ��i�� � ��ᨢi
    }
    while(posChanged != (cnt - 1) && func(rail[posChanged+1],stroka) == -1){ //横�: ���� �� �i�諨 �� �i��� ��ᨢ� i ������� �ॡ� ��⠢�� �ࠢi�
        void *temp = rail[posChanged]; //����i��� ����� �������
        rail[posChanged] = rail[posChanged+1]; //�� �i�� ������ �⠢��� ����㯭��
        rail[posChanged+1] = temp; //�� �i�� ����㯭��� �⠢��� �����
        posChanged++; //���室��� ��ࠢ� � ��ᨢi
    }
}

/* �㭪�i� ��������� �������(��i�쭥��� ���`��i)
 * ��ਬ�� ����i���� �� ��ᨢ ����i����i� � �����i� ������� ��� ��������� */
void del(void **&rail, int pos)
{
    int cnt = ((int*)rail)[POS_CNT]; //��ਬ�� �i��i��� ����i����i� � ��ᨢi ����i����i�
    void *wp = rail[pos]; //����i���� �� ������� ��� ���������
    for(int i = pos; i < cnt-1; i++) //横�: ��� �����稪i� �� �i�� ������ �����稪�
        rail[i] = rail[i+1]; //�i�����
    free(wp); //��i���� ���`���
    ((int*)rail)[POS_CNT] = cnt-1; //������� i��ଠ�i� � ��ᨢi �����稪i�
}

/* �㭪�i� ��������� ᯨ�� 3-��� �i���
 * ��ਬ�� ����i���� �� ��ᨢ ����i����i� */
void deletingTrip(void **&rail)
{
    int cnt = ((int*)rail)[POS_CNT]; //��ਬ�� �i��i��� ����i����i�
    for(int i = 0; i < cnt; i++) //横�: ���� �� �������� ��i �������
         del(rail, 0); //��i���� ���`���
}

/* �㭪�i� ��������� ᯨ�� 2-��� �i���
 * ��ਬ�� ����i���� �� ��ᨢ ����i����i� */
void deletingRailSt(void **&rail)
{
    int cnt = ((int*)rail)[POS_CNT]; //��ਬ�� �i��i��� ����i����i�
    for(int i = 0; i < cnt; i++){ //横�: ���� �� �������� ��i �������
         deletingTrip(((RailStation*)rail[i])->sublevel); //������ �㭪�i� ��������� ��� ��i� �������i� 3 �i��� - ����i�
         del(rail, 0); //��i���� ���`���
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

/* �㭪�i� ���०���� ᯨ�� � 䠩�
 * ��ਬ�� ����i���� �� ���⮪ ᯨ�� � ��� 䠩�� */
void saveToFile(void **rail, QString path)
{
    QString pattern = "\"%1\": %2,%3\n"; //i�i�i��i��� �����i��i ���୨
    QString pattern1 = "\"%1\": %2,%3,%4\n";
    QString pattern2 = "\"%1\": %2,%3,%4,%5,%6,%7,%8\n";
    QString pattern3 = "\"%1\": %2,%3,%4,%5,%6\n";
    QString tagRail = "R", tagCity = "C", tagRailSt = "V", tagTrip = "T"; //i�i�i��i��� �����i��i ���������, 鮡 �i��i���� ������� �� �i��������i

    QFile file(path); //�������� 䠩���� ��i���
    file.open(QIODevice::WriteOnly | QIODevice::Text); //�i��ਢ�� ⥪�⮢�� 䠩� �� �����

    Railway *railway = ((Railway*)rail[0]); //�����i��� ��i���
    file.write(pattern.arg(tagRail, railway->branch, railway->regions.join(",")).toUtf8()); //������� � 䠩�

    int aCity = ((int*)railway->sublevel)[POS_CNT]; //�i��i��� ����i����i� �� �i��i��i
    for(int j = 0; j < aCity; j++){ //横�: ��ॣ�� �������i�
        City *city = ((City*)railway->sublevel[j]); //�����i��� ��i���
        file.write(pattern1.arg(tagCity, city->city, city->region, city->type).toUtf8()); //������� � 䠩�
        if(city->sublevel == NULL) continue; //�� ����� �i��i���, � ���室��� �� ����㯭��� �������

        int aRailSt = ((int*)((City*)city)->sublevel)[POS_CNT]; //�i��i��� ����i����i� �� �i��i��i
        for(int k = 0; k < aRailSt; k++){ //横�: ��ॣ�� �������i�
            RailStation *railSt = ((RailStation*)city->sublevel[k]); //�����i��� ��i���
            file.write(pattern2.arg(tagRailSt, railSt->name, QString::number(railSt->pastrafic), QString::number(railSt->rails), QVariant(railSt->service.bathroom).toString(),
                                    QVariant(railSt->service.food).toString(), QVariant(railSt->service.vip).toString(),
                                    QVariant(railSt->service.wifi).toString()).toUtf8()); //������� � 䠩�
            if(railSt->sublevel == NULL) continue; //�� ����� �i��i���, � ���室��� �� ����㯭��� �������

            int aTrip = ((int*)((RailStation*)railSt)->sublevel)[POS_CNT]; //�i��i��� ����i����i� �� �i��i��i
            for(int m = 0; m < aTrip; m++){ //横�: ��ॣ�� �������i�
                Trip *trip = ((Trip*)railSt->sublevel[m]); //�����i��� ��i���
                file.write(pattern3.arg(tagTrip, QString::number(trip->duration), trip->from, trip->number, trip->regularity, trip->to).toUtf8()); //������� � 䠩�
            }
        }
    }
    file.close(); //���ਢ�� 䠩�
}

/* �㭪�i� �i�⢮७�� ᯨ�� i� 䠩��
 * ��ਬ�� ����i���� �� ���⮪ ᯨ�� i ��� 䠫� */
void retrieveFromFile(void **&rail, QString path)
{
    void **nrail = initArr(); //i�i�i��i��� ����� ᯨ᮪
    QFile file(path); //�������� 䠩���� ��i���
    QString tagRail ="\"R\":", tagCity ="\"C\": ", tagRailSt="\"V\": ", tagTrip ="\"T\": "; //�����襭�� �����i���� ��i���� ��� ������ �� �i����i���� �i����
    int aRail = 0, aCity = 0, aRailSt = 0, aTrip = 0; //�����i��i ��i��i

    file.open(QIODevice::ReadOnly | QIODevice::Text); //�i��ਢ�� ⥪�⮢�� 䠩� �� �⠭��

    while(!file.atEnd()){ //横�: ���� �� �i���� 䠩��
        QByteArray bytes = file.readLine(); //�����
        QString line(bytes); //����� �冷�
        line.remove("\n"); //�ਡ��� ������ ���室� �� ����㯭�� �冷�
        QStringList item = line.split(","); //i�i�i��i��� ��ᨢ ᨬ���쭨� �浪i� i� ��⠭��� �浪�, �� ������� ஧�i���i ����� i �஡i���

        if(line.startsWith(tagRail)){ //�� ��⠭�� �冷� �i�������� �� ������� �������
            item[0] = item[0].remove(tagRail); //�ਡ��� ������

            Railway *railway = new Railway; //���i��� ���'���
            railway->branch = item[0]; //���i�� i��ଠ�i��i ����
            for(int i = 1; i < 25; i++)
                railway->regions << item[i];
            railway->sublevel = initArr(); //i�i�i��i��� �i��i����

            addToSort(nrail, (void*)railway, aRail++); //����� �� ��⮢����� ᯨ��
            aCity = aRailSt = aTrip = 0; //�i��i��� �������i� �� ���� �i��i��� �� 0
        }
        else if(line.startsWith(tagCity)){ //�� ��⠭�� �冷� �i�������� �� ������� �i��
            item[0] = item[0].remove(tagCity); //�ਡ��� ������

            City *city = new City; //���i��� ���'���
            city->city = item[0]; //���i�� i��ଠ�i��i ����
            city->region = item[1];
            city->type = item[2];
            city->sublevel = initArr(); //i�i�i��i��� �i��i����

            addToSort(((Railway*)nrail[aRail-1])->sublevel, (void*)city, aCity++); //����� �� ��⮢����� ᯨ��
            aRailSt = aTrip = 0; //�i��i��� �������i� �� ���� �i��i��� �� 0
        }
        else if(line.startsWith(tagRailSt)){ //�� ��⠭�� �冷� �i�������� �� ������� ������
            item[0] = item[0].remove(tagRailSt); //�ਡ��� ������

            RailStation *railSt = new RailStation; //���i��� ���'���
            railSt->name = item[0]; //���i�� i��ଠ�i��i ����
            railSt->pastrafic = item[1].toInt();
            railSt->rails = item[2].toInt();
            railSt->service.bathroom = QVariant(item[3]).toBool();
            railSt->service.food = QVariant(item[4]).toBool();
            railSt->service.vip = QVariant(item[5]).toBool();
            railSt->service.wifi = QVariant(item[6]).toBool();
            railSt->sublevel = initArr(); //i�i�i��i��� �i��i����

            addToSort(((City*)((Railway*)nrail[aRail-1])->sublevel[aCity-1])->sublevel, (void*)railSt, aRailSt++);  //����� �� ��⮢����� ᯨ��
            aTrip = 0; //�i��i��� �������i� �� ���� �i��i�i 0
        }
        else if(line.startsWith(tagTrip)){ //�� ��⠭�� �冷� �i�������� �� ������� ����
            item[0] = item[0].remove(tagTrip); //�ਡ��� ������

            Trip *trip = new Trip; //���i��� ���'���
            trip->duration = item[0].toFloat();
            trip->from = item[1];
            trip->number = item[2];
            trip->regularity = item[3];
            trip->to = item[4];

            addToSort(((RailStation*)((City*)((Railway*)nrail[aRail-1])->sublevel[aCity-1])->sublevel[aRailSt-1])->sublevel, (void*)trip, aTrip++);  //����� �� ��⮢����� ᯨ��
         }
    }
    file.close(); //���ਢ�� 䠩�
    rail = nrail; //���i�� ᯨ᮪
}
