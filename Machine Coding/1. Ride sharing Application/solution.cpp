#include <iostream>
#include <vector>
using namespace std;

enum RideStatus {IDLE, CREATED, WITHDRAWN, COMPLETED};

class Ride
{
private:
    int id;
    int origin, dest;
    int seats;
    RideStatus rideStatus;

public:
    static const int AMT_PER_KM = 20;

    Ride()
    {
        id = origin = dest = seats = 0;
        rideStatus = RideStatus::IDLE;
    }

    int calculateFare(bool isPriorityRider)
    {
        int dist = dest - origin;
        if (seats < 2)
        {
            return dist * AMT_PER_KM * (isPriorityRider ? 0.75 : 1);
        }
        return dist * seats * AMT_PER_KM * (isPriorityRider ? 0.5 : 0.75);
    }

    void setDest(int dest) { this->dest = dest; }

    int getId() const { return id; }

    void setId(int id) { this->id = id; }

    void setOrigin(int origin) { this->origin = origin; }

    RideStatus getRideStatus() const { return rideStatus; }

    void setRideStatus(RideStatus rideStatus) { this->rideStatus = rideStatus; }

    void setSeats(int seats) { this->seats = seats; }
};

class Person
{
protected:
    string name;
};

class Driver : private Person
{
public:
    Driver(string name)
    {
        this->name = name;
    }
};

class Rider : private Person
{
private:
    int id;
    vector<Ride> completedRides;
    Ride currentRide;

public:
    Rider(int id, string name)
    {
        this->id = id;
        this->name = name;
    }

    void createRide(int id, int origin, int dest, int seats)
    {
        if (origin >= dest)
        {
            cout << "Wrong values of Origin and Destination provided. Can't create ride\n";
            return;
        }

        currentRide.setId(id);
        currentRide.setOrigin(origin);
        currentRide.setDest(dest);
        currentRide.setSeats(seats);
        currentRide.setRideStatus(RideStatus::CREATED);
    }

    void updateRide(int id, int origin, int dest, int seats)
    {
        if (currentRide.getRideStatus() == RideStatus::WITHDRAWN)
        {
            cout << "Can't update ride. Ride was withdrawn\n";
            return;
        }
        if (currentRide.getRideStatus() == RideStatus::COMPLETED)
        {
            cout << "Can't update ride. Ride already complete\n";
            return;
        }

        createRide(id, origin, dest, seats);
    }

    void withdrawRide(int id)
    {
        if (currentRide.getId() != id)
        {
            cout << "Wrong ride Id as input. Can't withdraw current ride\n";
            return;
        }
        if (currentRide.getRideStatus() != RideStatus::CREATED)
        {
            cout << "Ride wasn't in progress. Can't withdraw ride\n";
            return;
        }

        currentRide.setRideStatus(RideStatus::WITHDRAWN);
    }

    int closeRide()
    {
        if (currentRide.getRideStatus() != RideStatus::CREATED)
        {
            cout << "Ride wasn't in progress. Can't close ride\n";
            return 0;
        }

        currentRide.setRideStatus(RideStatus::COMPLETED);
        completedRides.push_back(currentRide);
        return currentRide.calculateFare(completedRides.size() >= 10);
    }

    int getId() const { return id; }
};

class System
{
private:
    int drivers;
    vector<Rider> riders;

public:
    System(int drivers, vector<Rider>& riders)
    {
        if (drivers < 2 || riders.size() < 2)
        {
            cout << "Not enough drivers or riders\n";
        }

        this->drivers = drivers;
        this->riders = riders;
    }

    void createRide(int riderId, int rideId, int origin, int dest, int seats)
    {
        if (drivers == 0)
        {
            cout << "No drivers around. Can't create ride\n";
            return;
        }

        for (Rider &rider : riders)
        {
            if (rider.getId() == riderId)
            {
                rider.createRide(rideId, origin, dest, seats);
                drivers--;
                break;
            }
        }
    }

    void updateRide(int riderId, int rideId, int origin, int dest, int seats)
    {
        for (Rider &rider : riders)
        {
            if (rider.getId() == riderId)
            {
                rider.updateRide(rideId, origin, dest, seats);
                break;
            }
        }
    }

    void withdrawRide(int riderId, int rideId)
    {
        for (Rider &rider : riders)
        {
            if (rider.getId() == riderId)
            {
                rider.withdrawRide(rideId);
                drivers++;
                break;
            }
        }
    }

    int closeRide(int riderId)
    {
        for (Rider &rider : riders)
        {
            if (rider.getId() == riderId)
            {
                drivers++;
                return rider.closeRide();
            }
        }
        return 0;
    }
};

int main()
{
    Rider rider(1, "Lucifer");
    Driver driver("Amenadiel");
    Rider rider1(2, "Chloe");
    Rider rider2(3, "Maze");

    vector<Rider> riders;
    riders.push_back(rider);
    riders.push_back(rider1);
    riders.push_back(rider2);
    System system(3, riders);

    rider.createRide(1, 50, 60, 1);
    cout << rider.closeRide() << endl;
    rider.updateRide(1, 50, 60, 2);
    cout << rider.closeRide() << endl;

    cout << "*****************************************************************" << endl;

    system.createRide(1, 1, 50, 60, 1);
    system.withdrawRide(1, 1);
    system.updateRide(1, 1, 50, 60, 2);
    cout << system.closeRide(1) << endl;

    cout << "*****************************************************************" << endl;

    system.createRide(1, 1, 50, 60, 1);
    system.updateRide(1, 1, 50, 60, 2);
    cout << system.closeRide(1) << endl;

    return 0;
}

/*


200
Can't update ride. Ride already complete
Ride wasn't in progress. Can't close ride
0
*****************************************************************
Can't update ride. Ride was withdrawn
Ride wasn't in progress. Can't close ride
0
*****************************************************************
300

*/
