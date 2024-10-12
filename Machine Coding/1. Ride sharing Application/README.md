+---------------------+
|       Person        |
+---------------------+
| - name: string      |
+---------------------+
| + Person()          |
+---------------------+
          ^
          |
          |
+---------------------+
|       Driver        |
+---------------------+
| + Driver(name: string) |
+---------------------+
          ^
          |
          |
+---------------------+
|       Rider         |
+---------------------+
| - id: int          |
| - completedRides: vector<Ride> |
| - currentRide: Ride |
+---------------------+
| + Rider(id: int, name: string) |
| + createRide(id: int, origin: int, dest: int, seats: int) |
| + updateRide(id: int, origin: int, dest: int, seats: int) |
| + withdrawRide(id: int) |
| + closeRide(): int    |
| + getId(): int        |
+---------------------+
          |
          |  has
          |  
          v
+---------------------+
|       Ride          |
+---------------------+
| - id: int           |
| - origin: int       |
| - dest: int         |
| - seats: int        |
| - rideStatus: RideStatus |
| - AMT_PER_KM: const int |
+---------------------+
| + Ride()            |
| + calculateFare(isPriorityRider: bool): int |
| + setDest(dest: int) |
| + getId(): int      |
| + setId(id: int)    |
| + setOrigin(origin: int) |
| + getRideStatus(): RideStatus |
| + setRideStatus(rideStatus: RideStatus) |
| + setSeats(seats: int) |
+---------------------+

          ^
          |
          |
+---------------------+
|       System        |
+---------------------+
| - drivers: int      |
| - riders: vector<Rider> |
+---------------------+
| + System(drivers: int, riders: vector<Rider>&) |
| + createRide(riderId: int, rideId: int, origin: int, dest: int, seats: int) |
| + updateRide(riderId: int, rideId: int, origin: int, dest: int, seats: int) |
| + withdrawRide(riderId: int, rideId: int) |
| + closeRide(riderId: int): int |
+---------------------+