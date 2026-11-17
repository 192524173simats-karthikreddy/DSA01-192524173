
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Member class for service information
class ServiceInfo
{
public:
    double fuelOrChargeLevel;
    string serviceDueDate;

    ServiceInfo(double level, string date)
    {
        fuelOrChargeLevel = level;
        serviceDueDate = date;
    }

    void display() const
    {
        cout << "Fuel/Charge Level: " << fuelOrChargeLevel << "%" << endl;
        cout << "Service Due Date: " << serviceDueDate << endl;
    }
};

// Abstract base class
class Vehicle
{
protected:
    string registrationNo;
    double dailyRate;
    bool rented;
    int rentalDays;

public:
    Vehicle(string reg, double rate)
    {
        registrationNo = reg;
        dailyRate = rate;
        rented = false;
        rentalDays = 0;
    }

    virtual double calculateCharge(int days) const = 0;

    bool rent(int days)
    {
        if (rented)
        {
            cout << registrationNo << " is already rented." << endl;
            return false;
        }

        if (days <= 0)
        {
            cout << "Invalid rental days." << endl;
            return false;
        }

        rented = true;
        rentalDays = days;

        cout << registrationNo << " rented successfully for "
             << days << " days." << endl;

        return true;
    }

    double returnVehicle(int lateDays)
    {
        if (!rented)
        {
            cout << registrationNo << " is not rented." << endl;
            return 0;
        }

        if (lateDays < 0)
        {
            cout << "Invalid late days." << endl;
            return 0;
        }

        double rentalCharge = calculateCharge(rentalDays);
        double lateCharge = lateDays * 200;
        double total = rentalCharge + lateCharge;

        rented = false;
        rentalDays = 0;

        cout << "\nRegistration Number: " << registrationNo << endl;
        cout << "Rental Charge: Rs. " << rentalCharge << endl;
        cout << "Late Charge: Rs. " << lateCharge << endl;
        cout << "Total Charge: Rs. " << total << endl;

        return total;
    }

    virtual void display() const
    {
        cout << "Registration Number: " << registrationNo << endl;
        cout << "Daily Rate: Rs. " << dailyRate << endl;
        cout << "Status: " << (rented ? "Rented" : "Available") << endl;
    }

    virtual ~Vehicle()
    {
    }
};

// Bicycle class
class Bicycle : public Vehicle
{
public:
    Bicycle(string reg, double rate)
        : Vehicle(reg, rate)
    {
    }

    double calculateCharge(int days) const override
    {
        return dailyRate * days;
    }

    void display() const override
    {
        cout << "\n--- BICYCLE ---" << endl;
        Vehicle::display();
    }
};

// Intermediate motor vehicle class
class MotorVehicle : public Vehicle
{
protected:
    ServiceInfo service;

public:
    MotorVehicle(string reg, double rate,
                 double level, string date)
        : Vehicle(reg, rate), service(level, date)
    {
    }

    void display() const override
    {
        Vehicle::display();
        service.display();
    }
};

// Two-wheeler class
class TwoWheeler : public MotorVehicle
{
    double fuelLitres;
    double pricePerLitre;

public:
    TwoWheeler(string reg, double rate, double level,
               string date, double fuel, double price)
        : MotorVehicle(reg, rate, level, date)
    {
        fuelLitres = fuel;
        pricePerLitre = price;
    }

    double calculateCharge(int days) const override
    {
        return (dailyRate * days) + (fuelLitres * pricePerLitre);
    }

    void display() const override
    {
        cout << "\n--- TWO WHEELER ---" << endl;
        MotorVehicle::display();
    }
};

// Car class
class Car : public MotorVehicle
{
protected:
    int seatingCapacity;
    double fuelLitres;
    double pricePerLitre;

public:
    Car(string reg, double rate, double level, string date,
        int seats, double fuel, double price)
        : MotorVehicle(reg, rate, level, date)
    {
        seatingCapacity = seats;
        fuelLitres = fuel;
        pricePerLitre = price;
    }

    double calculateCharge(int days) const override
    {
        return (dailyRate * days) + (fuelLitres * pricePerLitre);
    }

    void display() const override
    {
        cout << "\n--- CAR ---" << endl;
        MotorVehicle::display();
        cout << "Seating Capacity: " << seatingCapacity << endl;
    }
};

// Electric car class
class ElectricCar : public Car
{
    double batteryCapacity;
    double unitsUsed;
    double pricePerKWh;

public:
    ElectricCar(string reg, double rate, double level, string date,
                int seats, double battery, double units, double price)
        : Car(reg, rate, level, date, seats, 0, 0)
    {
        batteryCapacity = battery;
        unitsUsed = units;
        pricePerKWh = price;
    }

    double calculateCharge(int days) const override
    {
        return (dailyRate * days) + (unitsUsed * pricePerKWh);
    }

    void display() const override
    {
        cout << "\n--- ELECTRIC CAR ---" << endl;
        MotorVehicle::display();
        cout << "Seating Capacity: " << seatingCapacity << endl;
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// New vehicle type: Electric Bus
class ElectricBus : public MotorVehicle
{
    int seatingCapacity;
    double batteryCapacity;
    double unitsUsed;
    double pricePerKWh;

public:
    ElectricBus(string reg, double rate, double level, string date,
                int seats, double battery, double units, double price)
        : MotorVehicle(reg, rate, level, date)
    {
        seatingCapacity = seats;
        batteryCapacity = battery;
        unitsUsed = units;
        pricePerKWh = price;
    }

    double calculateCharge(int days) const override
    {
        return (dailyRate * days) + (unitsUsed * pricePerKWh);
    }

    void display() const override
    {
        cout << "\n--- ELECTRIC BUS ---" << endl;
        MotorVehicle::display();
        cout << "Seating Capacity: " << seatingCapacity << endl;
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    // Create vehicle objects dynamically
    Vehicle* fleet[5];

    fleet[0] = new Bicycle("BIKE101", 100);

    fleet[1] = new TwoWheeler(
        "TWO201", 300, 80, "20-12-2026", 2, 110
    );

    fleet[2] = new Car(
        "CAR301", 1000, 60, "25-12-2026", 5, 5, 100
    );

    fleet[3] = new ElectricCar(
        "EV401", 1500, 90, "30-12-2026", 5, 60, 20, 8
    );

    fleet[4] = new ElectricBus(
        "BUS501", 3000, 85, "31-12-2026", 40, 250, 30, 10
    );

    // Display all vehicles
    cout << "===== VEHICLE DETAILS =====" << endl;

    for (int i = 0; i < 5; i++)
    {
        fleet[i]->display();
    }

    // Rent all vehicles
    cout << "\n===== RENTING VEHICLES =====" << endl;

    for (int i = 0; i < 5; i++)
    {
        fleet[i]->rent(2);
    }

    // Return all vehicles
    cout << "\n===== RETURNING VEHICLES =====" << endl;

    for (int i = 0; i < 5; i++)
    {
        int lateDays = (i == 3) ? 2 : 0;

        fleet[i]->returnVehicle(lateDays);
        cout << "------------------------" << endl;
    }

    // Demonstrate adding a new vehicle type
    cout << "\n===== NEW VEHICLE TYPE =====" << endl;

    Vehicle* newVehicle = new ElectricBus(
        "BUS502", 3500, 95, "31-12-2026", 45, 300, 40, 10
    );

    newVehicle->display();

    cout << "Electric Bus Charge for 2 days: Rs. "
         << newVehicle->calculateCharge(2) << endl;

    delete newVehicle;

    // Release all fleet objects
    for (int i = 0; i < 5; i++)
    {
        delete fleet[i];
    }

    return 0;
}
