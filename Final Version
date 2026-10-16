
#include <iostream>
#include <cstdlib>
using namespace std;

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

class Router
{
    Packet *queue;
    int capacity;
    int front, rear, count;

    int generated, processed, lost, congestion;

public:
    Router(int c)
    {
        capacity = c;
        queue = new Packet[capacity];

        front = 0;
        rear = -1;
        count = 0;

        generated = 0;
        processed = 0;
        lost = 0;
        congestion = 0;
    }

    // Network congestion and packet loss
    void addPacket(int id)
    {
        generated++;

        if (count == capacity)
        {
            showBufferStatus();

            cout << "Packet " << id
                 << " dropped: No vacant slot available!\n";

            lost++;
            return;
        }

        rear = (rear + 1) % capacity;
        queue[rear] = Packet(id, rand() % 900 + 100);
        count++;

        cout << "Packet " << id << " arrived\n";

        if (count * 100 >= capacity * 80)
        {
            cout << "WARNING: Buffer occupancy is high!\n";
            congestion++;
        }
    }

    void processPacket()
    {
        if (count == 0)
        {
            cout << "Buffer is empty\n";
            return;
        }

        cout << "Processed Packet "
             << queue[front].id << endl;

        front = (front + 1) % capacity;
        count--;
        processed++;
    }

    // Network statistics and terminal output
    void showBufferStatus()
    {
        cout << "\nBuffer Status:\n";
        cout << "Occupied Slots : " << count << endl;
        cout << "Vacant Slots   : " << capacity - count << endl;

        if (count == capacity)
            cout << "ALERT: Buffer is FULL!\n";
        else if (count * 100 >= capacity * 80)
            cout << "WARNING: Buffer is nearly full!\n";
    }

    void showBuffer()
    {
        cout << "Packets in Buffer: ";

        if (count == 0)
            cout << "Empty";

        int index = front;

        for (int i = 0; i < count; i++)
        {
            cout << queue[index].id << " ";
            index = (index + 1) % capacity;
        }

        cout << endl;
    }

    void showResults()
    {
        cout << "\n===== FINAL RESULTS =====\n";
        cout << "Generated Packets : " << generated << endl;
        cout << "Processed Packets : " << processed << endl;
        cout << "Lost Packets      : " << lost << endl;
        cout << "Packets Remaining : " << count << endl;
        cout << "Congestion Alerts : " << congestion << endl;

        if (generated > 0)
            cout << "Packet Loss Rate  : "
                 << lost * 100.0 / generated << "%\n";
    }

    ~Router()
    {
        delete[] queue;
    }
};

int main()
{
    int capacity, steps, arrivals, processing;
    int id = 1;

    cout << "NETWORK TRAFFIC AND CONGESTION SIMULATOR\n";

    cout << "Enter buffer capacity: ";
    cin >> capacity;

    cout << "Enter Simulator time : ";
    cin >> steps;

    cout << "Packets arriving per step: ";
    cin >> arrivals;

    cout << "Packets processed per step: ";
    cin >> processing;

    if (capacity <= 0 || steps <= 0 ||
        arrivals < 0 || processing < 0)
    {
        cout << "Invalid input!\n";
        return 0;
    }

    Router router(capacity);

    for (int t = 1; t <= steps; t++)
    {
        cout << "\n========== Simulator Running Time Second No. " << t << " ==========\n";

        // Packet generation
        cout << "\nPacket Arrival:\n";

        for (int i = 0; i < arrivals; i++)
        {
            router.addPacket(id);
            id++;
        }

       
 // Buffer status before processing
        cout << "\nStatus Before Processing:\n";
        router.showBufferStatus();
        router.showBuffer();

        cout << "\nPacket Processing:\n";

        for (int i = 0; i < processing; i++)
            router.processPacket();

        // Buffer status after processing
        cout << "\nStatus After Processing:\n";
        router.showBufferStatus();
        router.showBuffer();
    }

    router.showResults();

    return 0;
}
