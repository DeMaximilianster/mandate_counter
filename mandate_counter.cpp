// mandate_counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Party
{
private:
	string name = "";
	int votes = 0;
	int mandates = 0;
	double support = 0.0;
	double points = 0.0;

public:
	void setName(string newName) {
		name = newName;
	};
	string getName() {
		return name;
	};
	void setVotes(int newVotes) {
		votes = newVotes;
	};
	int getVotes() {
		return votes;
	};
	void calculateSupport(double totalVotes) {
		support = round(votes / totalVotes * 100); // support is unchangable attribute 
	};
	double getSupport() {
		return support;
	};
	void clear() {
		points = support;
		mandates = 0;
	};
	void setPoints(double newPoints) {
		points = newPoints;
	};
	double getPoints() {
		return points;
	};
	void setMandates(int newMandates) {
		mandates = newMandates;
	};
	void addMandate() {
		mandates++;
	}
	int getMandates() {
		return mandates;
	};
};

int main(int argc, char** argv)
{
	setlocale(0, "rus");
	system("chcp 1251");
	int partiesNum, i, j, newVotes, allMandates, pointsForMandate, mandates, leftMandates, points;
	// variables for sorting in step 6
	double sorterValue;
	int sorterIndex; 
	double totalVotes = 0.0;
	string newName;
	Party parties[15], sortedParties[15], party;

	cout << "Шаг 1. Введение данных" << endl;
	cout << "Введите количество партий на выборах: ";
	cin >> partiesNum;

	for (i = 0; i < partiesNum; i++) {
		cout << "Введите название партии " << i + 1 << ": ";
		cin >> newName;
		parties[i].setName(newName);
		cout << "Введите количество голосов за партию " << i + 1 << ": ";
		cin >> newVotes;
		parties[i].setVotes(newVotes);
		totalVotes += newVotes;

	};
	cout << "Шаг 2. Вычисление процентов " << endl;
	cout << "Всего голосов: " << totalVotes << endl;
	for (i = 0; i < partiesNum; i++) {
		parties[i].calculateSupport(totalVotes);
		cout << parties[i].getName() << " - " << parties[i].getSupport() << "%" << endl;
	};
	cout << "Шаги 3-7. Собственно подсчёт мандатов" << endl;
	for (allMandates = 5; allMandates <= 100; allMandates++) {
		cout << "Шаг 3. Ставим количество мандатов m=" << allMandates << endl;
		pointsForMandate = 100 / allMandates;
		cout << "Шаг 4. Рассчитываем количество процентов за мандат k=[100/m]=" << pointsForMandate << endl;
		leftMandates = allMandates;
		cout << "Шаг 5. Раздаём партиям мандаты за каждое полное число k процентов" << endl;
		for (i = 0; i < partiesNum; i++) {
			parties[i].clear();  // start counting mandates
			// exchange points for mandates
			points = parties[i].getPoints();
			mandates = points / pointsForMandate;
			points = points % pointsForMandate;
			parties[i].setMandates(mandates);
			leftMandates -= mandates;
			parties[i].setPoints(points);
			cout << "Партия " << parties[i].getName() << " получает мандатов: " << mandates;
			cout << " и оставляет очков: " << points << endl;
		};
		cout << "Шаг 6. Рассортируем партии по оставшимся очкам" << endl;
		for (i = 0; i < partiesNum; i++) {
			sorterValue = -1.0;
			sorterIndex = 0;
			for (j = 0; j < partiesNum; j++) {
				if (parties[j].getPoints() > sorterValue) {
					sorterValue = parties[j].getPoints();
					sorterIndex = j;
				};	
			}
			sortedParties[i] = parties[sorterIndex];
			parties[sorterIndex].setPoints(-1.0);  // program won't put this party again
		}
		// print sorted array
		for (i = 0; i < partiesNum; i++) {
			cout << "Партия " << sortedParties[i].getName() << ". Очков: " << sortedParties[i].getPoints();
			cout << endl;
		};
		cout << "Шаг 7. Распределим между партиями оставшиеся мандаты в количестве " << leftMandates;
		cout << endl;
		for (i = 0; i < leftMandates; i++) {
			sortedParties[i].addMandate();
			cout << "Партия " << sortedParties[i].getName() << " получила мандат" << endl;
		}
		if (sortedParties[i].getPoints() == sortedParties[i - 1].getPoints()) {
			cout << "Распределение не вышло, возвращаемся к шагу 3" << endl;
		}
		else{
			cout << "Распределение успешно" << endl;
			break;
		}
	};
	cout << "Шаг 8. Печать результатов" << endl;
	for (i = 0; i < partiesNum; i++) {
		cout << sortedParties[i].getName() << ". Мандаты: " << sortedParties[i].getMandates() << endl;
	}
	return 0;
}
