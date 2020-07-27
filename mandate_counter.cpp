// mandate_counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Party
{
private:
	string name;
	int votes;
	int mandates;
	double points;

public:
	Party(){
		name = "";
		votes = 0;
		mandates = 0;
		points = 0.0;
	}
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
	double calculateSupport(double totalVotes) {
		return round(votes / totalVotes * 100);
	};
	void clear(double totalVotes) {
		points = calculateSupport(totalVotes);
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
	int partiesNum, newVotes, allMandates, pointsForMandate, mandates, leftMandates, points, partyIndex;
	// variables for sorting in step 6
	double sorterValue;
	int sorterIndex; 
	double totalVotes = 0.0;
	string newName, stream;
	Party party;

	cout << "Шаг 1. Введение данных" << endl;
	cout << "Введите количество партий на выборах: ";
	getline(cin, stream); 
	partiesNum = stoi(stream);

	Party *parties = new Party[partiesNum];
	Party *outputParties = new Party[partiesNum];

	for (int i = 0; i < partiesNum; i++) {
		cout << "Введите название партии " << i + 1 << ": ";
		getline(cin, newName);
		parties[i].setName(newName);
		cout << "Введите количество голосов за партию " << i + 1 << ": ";
		getline(cin, stream);
		newVotes = stoi(stream);
		parties[i].setVotes(newVotes);
		totalVotes += newVotes;

	};
	cout << "Шаг 2. Вычисление процентов " << endl;
	cout << "Всего голосов: " << totalVotes << endl;
	for (int i = 0; i < partiesNum; i++) {
		cout << parties[i].getName() << " - " << parties[i].calculateSupport(totalVotes) << "%" << endl;
	};
	cout << "Шаги 3-7. Собственно подсчёт мандатов" << endl;
	for (allMandates = 5; allMandates <= 100; allMandates++) {
		cout << "Шаг 3. Ставим количество мандатов m=" << allMandates << endl;
		pointsForMandate = 100 / allMandates;
		cout << "Шаг 4. Рассчитываем количество процентов за мандат k=[100/m]=" << pointsForMandate << endl;
		leftMandates = allMandates;
		cout << "Шаг 5. Раздаём партиям мандаты за каждое полное число k процентов" << endl;
		for (int i = 0; i < partiesNum; i++) {
			parties[i].clear(totalVotes);  // start counting mandates
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
		if (leftMandates > 0) {
			cout << "Шаг 6. Рассортируем партии по оставшимся очкам" << endl;
			for (int i = 0; i < partiesNum; i++) {
				sorterValue = -1.0;
				sorterIndex = 0;
				for (int j = 0; j < partiesNum; j++) {
					if (parties[j].getPoints() > sorterValue) {
						sorterValue = parties[j].getPoints();
						sorterIndex = j;
					};
				}
				outputParties[i] = parties[sorterIndex];
				parties[sorterIndex].setPoints(-1.0);  // program won't put this party again
			}
			// print sorted array
			for (int i = 0; i < partiesNum; i++) {
				cout << "Партия " << outputParties[i].getName() << ". Очков: " << outputParties[i].getPoints();
				cout << endl;
			};
			cout << "Шаг 7. Распределим между партиями оставшиеся мандаты в количестве " << leftMandates;
			cout << endl;
			for (partyIndex= 0; partyIndex < leftMandates; partyIndex++) {
				outputParties[partyIndex].addMandate();
				cout << "Партия " << outputParties[partyIndex].getName() << " получила мандат" << endl;
			}
			if (outputParties[partyIndex].getPoints() == outputParties[partyIndex - 1].getPoints()) {
				cout << "Распределение не вышло, возвращаемся к шагу 3" << endl;
			}
			else {
				cout << "Распределение успешно" << endl;
				break;
			}
		}
		else {
			cout << "Всё сошлось идеально, так что пропускаем шаги 6 и 7 ";
			cout << "(сортировка партий и распределение мандатов)" << endl;
			for (int i = 0; i < partiesNum; i++) {
				outputParties[i] = parties[i];
			}
			break;
		}
	};
	cout << "Шаг 8. Печать результатов" << endl;
	for (int i = 0; i < partiesNum; i++) {
		cout << outputParties[i].getName() << ". Мандаты: " << outputParties[i].getMandates() << endl;
	}
	return 0;
}
