#include "pch.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <ctime>
using namespace std;

bool pred(pair< char, double > &a, pair< char, double > &b)
{
	return a.second > b.second;
}
int main()
{
	map <char, double> alf;
	ifstream alph("alphabet.txt");
	ofstream out("out.txt");
	char c;
	{
		alph.get(c);
		alf[c] = 8.167;//a
		alph.get(c);
		alf[c] = 1.492;//b
		alph.get(c);
		alf[c] = 2.782;//c
		alph.get(c);
		alf[c] = 4.253;//d
		alph.get(c);
		alf[c] = 12.702;//e
		alph.get(c);
		alf[c] = 2.228;//f
		alph.get(c);
		alf[c] = 1.974;//g
		alph.get(c);
		alf[c] = 5.987;//h
		alph.get(c);
		alf[c] = 6.749;//i
		alph.get(c);
		alf[c] = 0.140;//j
		alph.get(c);
		alf[c] = 0.772;//k
		alph.get(c);
		alf[c] = 4.025;//l
		alph.get(c);
		alf[c] = 2.406;//m
		alph.get(c);
		alf[c] = 6.966;//n
		alph.get(c);
		alf[c] = 7.507;//o
		alph.get(c);
		alf[c] = 1.929;//p
		alph.get(c);
		alf[c] = 0.095;//q
		alph.get(c);
		alf[c] = 6.327;//r
		alph.get(c);
		alf[c] = 6.094 ;//s
		alph.get(c);
		alf[c] = 9.056;//t
		alph.get(c);
		alf[c] = 2.758;//u
		alph.get(c);
		alf[c] = 0.978;//v
		alph.get(c);
		alf[c] = 2.360;//w
		alph.get(c);
		alf[c] = 0.153;//x
		alph.get(c);
		alf[c] = 2.015;//y
		alph.get(c);
		alf[c] = 0.074;//z
	}
	
	for (auto it = alf.begin(); it != alf.end(); ++it) {
		out << (*it).first<<'=' << (*it).second <<'%'<< endl;
	}
	out << endl;

	//создаем вектор из map'a
	vector < pair< char, double > > vec1(alf.begin(), alf.end());

	//сортируем этот вектор по значению
	sort(vec1.begin(), vec1.end(), pred);

	//вывод 
	for (auto o : vec1) {
		out << o.first << '=' << o.second << endl;
	};
	
	ifstream alph2("alphabet2.txt");
	ifstream closedtext("text.txt");
	ofstream output("output.txt");
	map <char, double> alf2;
	char ch = alph2.get();
	while (!alph2.eof()) {
		alf2[ch] = 0;
		ch = alph2.get();
	};

	int all2 = 0;

	while (!closedtext.eof()) {
		char symbol2 = closedtext.get();
		for (auto it = alf2.begin(); it != alf2.end(); ++it) {
			if ((*it).first == symbol2) {
				(*it).second++;
				all2++;
			}
		}
	};


	for (auto it = alf2.begin(); it != alf2.end(); ++it) {
		double y = (*it).second;
		y = y / all2 * 100;
		(*it).second = y;
		output << (*it).first << "=" << y << "%" << endl;
	};
	output << endl;

	//создаем вектор из map'a
	vector < pair< char, double > > vec2(alf2.begin(), alf2.end());

	//сортируем этот вектор по значению
	sort(vec2.begin(), vec2.end(), pred);

	//вывод 
	for (auto o : vec2) {
		output << o.first << '=' << o.second << endl;
	};

	//начальный вариант ключа
		vector <pair<char, char>> KEY;
		vector <pair<char, char>> key;//текущий ключ, который буду изменять на каждой итерации в цикле

		for (int i = 0; i < 26; i++) {
			key.push_back(make_pair(vec1[i].first, vec2[i].first));
			KEY.push_back(make_pair(vec1[i].first, vec2[i].first));
		}
		
		vector<pair<double, double>> IOP;//начальный вектор частот
		vector<pair<double, double>> iop;//текущие частоты 

		for (int i = 0; i < 26; i++) {
			iop.push_back(make_pair(vec1[i].second, vec2[i].second));
			IOP.push_back(make_pair(vec1[i].second, vec2[i].second));
		}

		for (int i = 0; i < 26; i++) {
			cout << key[i].first << '=' << key[i].second << endl;
			cout << iop[i].first << '=' << iop[i].second << endl;
		}
	
	double diff[26];//использую простой массив для хранения разности частот 
	double d = 0;//здесь будет хранится сумма разностей частот начального варианта ключа 
	double d1 = 0;//текущая сумма разностей частот
	for(int i=0;i<26;i++){
		diff[i] = fabs(vec1[i].second - vec2[i].second);
		d += diff[i];
	}
	cout << d;
	srand(time(0));//функция, чтобы генерировать разные числа 
	int qwerty = 0;
	ofstream t("temp.txt");
	
	while (qwerty<=100)
	{
		int a = rand() % 27;
		int b = rand() % 27;
		
		double temp_1 = key[a].second;
		key[a].second = key[b].second;
		key[b].second = temp_1;
		double temp_2 = iop[a].second;
		iop[a].second = iop[b].second;
		iop[b].second = temp_2;

		for (int i = 0; i < 26; i++) {
			diff[i] = fabs(iop[i].first - iop[i].second);
			d1 += diff[i];
		}
		t << d1 <<endl ;

		if (d1<d) {
			qwerty = 0;
			KEY = key;
			IOP=iop;
		}

		d1 = 0;
		key = KEY;
		iop=IOP;

		qwerty++;
	}

	for (int i = 0; i < 26; i++) {
		t << KEY[i].first << '=' << KEY[i].second << endl;
	};

	ifstream text("text1.txt");
	ofstream deshifr("deshifr_text.txt");
	char s;
	while (!text.eof()) {
		s = text.get();
		for (int i = 0; i < 26;i++) {
			if (s == KEY[i].second ) {
				s=KEY[i].first;
				break;
			}
			else if (char(int(s) + 32) == KEY[i].second) {
				s = char(int(KEY[i].first) - 32);
				break;
			}
		}
		deshifr << s;
	};

	alph.close();
	out.close();
	alph2.close();
	output.close();
	closedtext.close();
	t.close();
	text.close();
	deshifr.close();
	return 0;
}

