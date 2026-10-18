
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// Packet class
class Packet
{
public:
    int id;
    int size;

    Packet()
    {
        id = 0;
        size = 0;
    }

    Packet(int i, int s)
    {
        id = i;
        size = s;
    }
};

// Router class
class Router
{
    Packet *queue;
    int capacity;
    int front, rear, count;

    int generated, processed, lost, congestion;

public:
    Router(int cap)
    {
        capacity = cap;
        queue = new Packet[capacity];

        front = 0;
        rear = -1;
        count = 0;

        generated = 0;
        processed = 0;
        lost = 0;
        congestion = 0;
    }

    ~Router()
    {
        delete[] queue;
    }

    // Display buffer occupancy
    void showBufferStatus()
    {
        cout << "\nBuffer Occupied: " << count
             << "/" << capacity;

        cout << "\nBuffer Vacant: "
             << capacity - count;

        if (count == capacity)
        {
            cout << "\nBUFFER FULL!";
        }
        else if (count * 100 >= capacity * 80)
        {
            cout << "\nWARNING: Buffer is nearly full!";
        }

        cout << endl;
    }

    // Add packet to router buffer
    void addPacket(int id)
    {
        generated++;

        if (count == capacity)
        {
            showBufferStatus();

            cout << "Packet " << id
                 << " dropped due to buffer overflow!\n";

            lost++;
            return;
        }

        rear = (rear + 1) % capacity;

        queue[rear] = Packet(id, rand() % 900 + 100);

        count++;

        cout << "Packet " << id
             << " arrived. Size: "
             << queue[rear].size << " bytes\n";

        if (count * 100 >= capacity * 80)
        {
            cout << "CONGESTION WARNING!\n";
            congestion++;
        }
    }
    // Process packet from router buffer
    void processPacket()
    {
        if (count == 0)
        {
            cout << "No packet available to process.\n";
            return;
        }

        cout << "Processing Packet "
             << queue[front].id << endl;

        front = (front + 1) % capacity;
        count--;
        processed++;
    }
    // Display packets currently in buffer
    void showBuffer()
    {
        if (count == 0)
        {
            cout << "Router buffer is empty.\n";
            return;
        }

        cout << "Packets in buffer: ";

        int index = front;

        for (int i = 0; i < count; i++)
        {
            cout << queue[index].id << " ";
            index = (index + 1) % capacity;
        }

        cout << endl;
    }
    // Display final network statistics
    void showResults()
    {
        cout << "\n========== FINAL RESULTS ==========\n";

        cout << "Total Packets Generated: "
             << generated << endl;

        cout << "Packets Processed: "
             << processed << endl;

        cout << "Packets Lost: "
             << lost << endl;

        cout << "Packets Remaining in Buffer: "
             << count << endl;

        cout << "Congestion Warnings: "
             << congestion << endl;

        if (generated > 0)
        {
            double lossRate = (lost * 100.0) / generated;

            cout << "Packet Loss Rate: "
                 << lossRate << "%\n";
        }
        else
        {
            cout << "Packet Loss Rate: 0%\n";
        }
        cout << "===================================\n";
    }
};
// Traffic Pattern Controller
int selectTrafficMode(int mode, int arrivals, int processing)
{
    int packets = arrivals;

    switch (mode)
    {
        case 1:
            // Low Traffic
            packets = 1;
            break;

        case 2:
            // Heavy Traffic
            packets = processing + 3;
            break;

        case 3:
            // Random Traffic
            if (arrivals > 0)
            {
                packets = rand() % (arrivals + 1);
            }
            else
            {
                packets = 0;
            }
            break;

        default:
            packets = arrivals;
    }

    return packets;
}

// Main function
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int capacity, steps;
    int arrivals, processing;
    int mode;

    cout << "===== NETWORK TRAFFIC AND CONGESTION SIMULATOR =====\n";

    cout << "Enter router buffer capacity: ";
    cin >> capacity;

    cout << "Enter total simulation steps: ";
    cin >> steps;

    cout << "Enter base packet arrivals per step: ";
    cin >> arrivals;

    cout << "Enter packets processed per step: ";
    cin >> processing;

    if (capacity <= 0 || steps <= 0 ||
        arrivals < 0 || processing < 0)
    {
        cout << "Invalid input! Please enter valid values.\n";
        return 0;
    }

    cout << "\nSelect Traffic Mode:\n";
    cout << "1. Low Traffic\n";
    cout << "2. Heavy Traffic\n";
    cout << "3. Random Traffic\n";
    cout << "Enter your choice: ";
    cin >> mode;

    if (mode < 1 || mode > 3)
    {
        cout << "Invalid traffic mode!\n";
        return 0;
    }

    Router router(capacity);

    int id = 1;

    // Simulation loop
    for (int t = 1; t <= steps; t++)
    {
        cout << "\n========== TIME STEP "
             << t << " ==========\n";

        // Determine arrivals for this time step
        int currentArrivals = selectTrafficMode(
            mode, arrivals, processing
        );

        cout << "Packets arriving this step: "
             << currentArrivals << endl;

        // Packet arrival phase
        cout << "\n--- PACKET ARRIVAL PHASE ---\n";

        for (int i = 0; i < currentArrivals; i++)
        {
            router.addPacket(id);
            id++;
        }

        router.showBufferStatus();
        router.showBuffer();

        // Packet processing phase
        cout << "\n--- PACKET PROCESSING PHASE ---\n";

        for (int i = 0; i < processing; i++)
        {
            router.processPacket();
        }

        router.showBufferStatus();
        router.showBuffer();
    }
    // Final results
    router.showResults();

    return 0;
}
