#include <iostream> // C++
#include <string> // Habilita String
#include <stdio.h> // C

using namespace std;

class FlightBooking { //cria-se o objeto FlightBooking
	public: //métodos públicos
		FlightBooking(int id, int capacity, int reserved); //criar/instanciar
		void printStatus(); //mostrar 
		bool reserveSeats(int number_of_seats); //reservarmos
		bool cancelReservations(int number_of_seats); //cancelarmos reservas
	private: //atributos privados
		int id; 
		int capacity;
		int reserved;
};

FlightBooking::FlightBooking(int id, int capacity, int reserved) {
	// Save data to members according to limits
	this->id = id;
	this->capacity = (capacity > 0) ? capacity : 0;
	this->reserved = (reserved > 0) ? reserved : 0;
	
	if ((100 * this->reserved) > ( 105 * this->capacity)) {
		this->reserved = (105 * this->capacity) / 100;
	}
}

bool FlightBooking::reserveSeats(int number_of_seats) {
	// try to add reservations and return 'true' on success
	if (number_of_seats <= 0 || (100 * (reserved + number_of_seats)) > ( 105 * capacity)) {
		return false;
	}
	reserved += number_of_seats;
	return true;
}

bool FlightBooking::cancelReservations(int number_of_seats) {
	// try to canel reservations and return 'true' on success
	if (number_of_seats <= 0 || reserved < number_of_seats) {
		return false;
	}
	reserved -= number_of_seats;
	return true;
}
void FlightBooking::printStatus() {
	cout << "Voo " << id << " : " << reserved << '/' << capacity << " (" << (100 * reserved) / capacity << "%) assentos reservados." << std::endl;
}

int main() {
	int reserved = 0,
	capacity = 0;
	cout << "Informe a capacidade do voo: ";
	cin >> capacity;
	cout << "Informe os assentos reservados: ";
	cin >> reserved;
	FlightBooking booking(1, capacity, reserved);
	
	string command = "";
	while (command != "sair") {
		int seats = 0;
		bool command_known = false;
		bool command_ok = false;
		booking.printStatus();
		cout << "O que voce quer fazer?: ";
		command = "";
		while (command == "") {
			getline(cin, command);
		}
		if (command == "sair") {
			command_known = true;
			command_ok = true;
		}
		
		if (0 != sscanf(command.c_str(), "add %d", &seats)) {
			command_known = true;
			command_ok = booking.reserveSeats(seats);
		} else if (0 != sscanf(command.c_str(), "cancel %d", &seats)) {
			command_known = true;
			command_ok = booking.cancelReservations(seats);
		}
		if (command_known && !command_ok) {
			cout << "Nao e possivel realizar a operacao" << endl;
		}
		if (!command_known) {
			cout << "Comando desconhecido" << endl;
		}
	}
	return 0;
}
