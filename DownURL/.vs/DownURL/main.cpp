#define CURL_STATICLIB
#include <stdio.h>
#include <curl/curl.h>
#include <locale.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


using namespace std;

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main()
{
    setlocale(LC_ALL, "ru");


    //���������� ���������� cUrl. Html ������ �������, ����� ������ ���������� ����)
    CURL* curl;
    FILE* fp;
    CURLcode res;
    const char* l = "https://lenta.ru/news/2020/08/14/transfer/";
    char outfilename[FILENAME_MAX] = "C:\\2.txt";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wt");
        curl_easy_setopt(curl, CURLOPT_URL, l);
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    

    string temp; //������ �� ������� ���������� ������
    ifstream fin("C:\\2.txt");

    int start=0; //������� ������ <p>
    int finish=0; //������� ����� </p>
    string tmpstr; // ��������� ������ ��� ������ � ����
    int range=0; //�������� �� ������ <p> �� ����� </p>
    int count=0; //������� ������, ����� ������
    int s=0; // ���� ������� ������ <p>
    int f=0; // ���� ������� ����� <p>

    std::ofstream out;			// ����� ��� ������
    out.open("C:\\3.txt"); // �������� ���� ��� ������

    //����� � ������ �����, ����� ��������� ���� � ����������� ������

    while (getline(fin, temp))
    {
        count = 0; 
        for (int x = 0; x < temp.size(); x++) //����������� ������,���������� ������ ������ � �����! ����� ��� ��������� �����
        {
            count += 1; //�������

            if (temp[x] == '<') 
            {
                int y = x + 1;
                if (temp[y] == 'p')
                {
                    int z = x + 2;
                    if (temp[z] == '>')
                    {
                        start = x + 3;
                        s = 1; //���� ����� �� ������ ���� start � ��������� 1
                    }

                }
            }

            if (temp[x] == '<')
            {
                int y = x + 1;
                if (temp[y] == '/');
                {
                    int k = x + 2;
                    if (temp[k] == 'p')
                    {
                        int g = x + 3;
                        if (temp[g] == '>')
                        {
                            finish = x;
                            f = 1; //���� ����� �� ������ ���� finish � ��������� 1
                        }
                    }
                    
                }

            }

            

            if (s == 0 and f == 0 and count == temp.length()) //��� ���������, ������� ������
            {
                tmpstr = temp;
                tmpstr.clear();
                out << " " << endl;
                s = 0;  //������� � ���� ����� ����� � �����
                f = 0;
            }
            
            if (s == 1 and f == 1 and count != temp.length()) //���� <p> � </p> � ��� �� ����� ������, ������ ����� ����� ������ ���������� � ����������� ������
            {
                if (start < finish)  //���� ������� <p> < </p> ������ ����� ���� ����� ����
                {
                    range = finish - start;
                    tmpstr = temp.substr(start, range);
                    out << tmpstr << endl;
                    tmpstr.clear();

                    start = 0;
                    finish = 0;

                    s = 0;
                    f = 0;
                }
                else  
                {
                    tmpstr = temp.substr(0, finish);  
                    out << tmpstr << endl;
                    out << " " << endl;
                    tmpstr.clear();
                    finish = 0;
                    f = 0;
                }
            }

            if (s == 1 and f == 0 and count == temp.length()) // ���� ������ <p> �� ���� ������, ������ ������ ���� � ���� �� ����� ������
            {
                range = count - start;
                tmpstr = temp.substr(start, range);
                out << tmpstr << endl;
                tmpstr.clear();

                start = 0;
                finish = 0;

                s = 0;
                f = 0;
            }

            if (s == 0 and f == 1 and count == temp.length()) //���� ������ </p> � ����� ������, ������ ����� ���� �� ������ � �� ����
            {
                tmpstr = temp.substr(0, finish);
                out << tmpstr << endl;
                tmpstr.clear();

                start = 0;
                finish = 0;

                s = 0;
                f = 0;
            }
        }
    }
    out.close();
    fin.close();
    return 0;
 }
  
