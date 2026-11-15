#include <iostream>
#include <cstdlib>
using namespace std;

// Packet class
class Packet{
public:
    int id, size;
    Packet(int i=0,int s=0){
        id=i;
        size=s;
    }
};

// Router class
class Router{
public:
    Packet *queue;
    int capacity, front, rear, count;
    int bandwidth, processed;

    Router(int c, int b){
        capacity=c;
        bandwidth=b;
        queue=new Packet[capacity];
        front=0;
        rear=-1;
        count=0;
        processed=0;
    }

    // Add packet to circular queue
    void addPacket(Packet p){
        rear=(rear + 1) % capacity;
        queue[rear]=p;
        count++;
        cout<<"Packet " << p.id << " added.\n";
    }

    // Process packets according to bandwidth
    void processPackets(){
        int used=0;
        while(count>0){
            if(used+queue[front].size>bandwidth)
                break;
            cout<<"Processed Packet "<<queue[front].id << endl;
            used +=queue[front].size;
            processed++;
            front=(front + 1) % capacity;
            count--;
        }

        if(count==0){
            front=0;
            rear=-1;
        }

        cout << "Bandwidth Used: "
             << used << "/" << bandwidth << " bytes\n";
    }

    // Display router status
    void showStatus(int n){
        cout<< "\nRouter " << n << endl;
        cout<< "Occupied: " << count << "/" << capacity << endl;
        cout<< "Vacant: " << capacity - count << endl;

        cout<< "Packets: ";

        if(count==0)
            cout << "Empty";
        else{
            int i=front;

            for(int j =0; j <count; j++)
            {
                cout<<queue[i].id << " ";
                i=(i + 1) % capacity;
            }
        }

        cout << endl;
    }

    ~Router()
    {
        delete[] queue;
    }
};

// Network class
class Network{
public:
    Router r1, r2, r3;
    Router *routers[3];

    int generated, redirected, dropped;

    Network(int c, int b1, int b2, int b3): r1(c, b1), r2(c, b2), r3(c, b3){
        routers[0]=&r1;
        routers[1]=&r2;
        routers[2]=&r3;

        generated=0;
        redirected=0;
        dropped=0;
    }

    // Find least occupied available router
    int findNextHop(){
        int best = -1;
        for(int i= 1;i < 3;i++){
            if(routers[i]->count==routers[i]->capacity){
                continue;
            }
            if(best==-1|| routers[i]->count<routers[best]->count){
                best = i;
            }
        }
        return best;
    }

    // Decide where packet should go
    void routePacket(Packet p){
        generated++;
        if (r1.count*100<r1.capacity*80){
            r1.addPacket(p);
        }
        else{
            cout << "Router 1 reached 80% occupancy.\n";
            int next = findNextHop();
            if (next!=-1){
                cout<<"Redirecting Packet "<< p.id<<" to Router "<< next+1<<endl;
                routers[next]->addPacket(p);
                redirected++;
            }
            else{
                cout<<"All routers are full.\n";
                cout<<"Packet " << p.id<<" dropped.\n";
                dropped++;
            }
        }
    }

    // Process all routers
    void processAllRouters(){
        for (int i=0;i<3;i++){
            cout<<"\nProcessing Router "<<i+1<<endl;
            routers[i]->processPackets();
        }
    }

    // Display all router statuses
    void showNetworkStatus(){
        for(int i=0;i<3;i++){
            routers[i]->showStatus(i+1);
        }
    }

    // Display final results
    void showResults(){
        int totalProcessed=0;
        int remaining=0;
        for (int i=0;i<3;i++){
            totalProcessed+=routers[i]->processed;
            remaining+=routers[i]->count;
        }

        cout<<"\n========== FINAL RESULTS ==========\n";

        cout<<"Generated: " << generated << endl;
        cout<<"Redirected: " << redirected << endl;
        cout<<"Processed: " << totalProcessed << endl;
        cout<<"Dropped: " << dropped << endl;
        cout<<"Remaining: " << remaining << endl;

        cout<<"\nPacket Accounting: ";

        if(generated==totalProcessed+dropped+remaining){
            cout<<"Correct";
        }
        else{
            cout<<"Incorrect";
        }
        cout<<endl;
    }
};

// Select traffic mode
int selectTrafficMode(){
    int choice;
    cout<<"\n1. Low Traffic";
    cout<<"\n2. High Traffic";
    cout<<"\n3. Random Traffic";
    cout<<"\nEnter choice: ";
    cin>>choice;
    return choice;
}

// Generate number of arriving packets
int generateTraffic(int mode, int arrivals){
    if(mode==1){
        return 1;
    }
    if(mode==2){
        return arrivals;
    }
    return rand() % (arrivals + 1);
}
// Main function
int main(){
    int capacity, b1, b2, b3;
    int steps, arrivals;
    cout<<"Enter buffer capacity: ";
    cin>>capacity;
    cout<<"Enter Router 1 bandwidth: ";
    cin>>b1;
    cout<<"Enter Router 2 bandwidth: ";
    cin>>b2;
    cout<<"Enter Router 3 bandwidth: ";
    cin>>b3;
    cout<<"Enter simulation steps: ";
    cin>>steps;
    cout<<"Enter maximum packet arrivals per step: ";
    cin>>arrivals;
    if(capacity<=0||b1<999||b2<999||b3<999||steps<0||arrivals<1){
        cout<<"Invalid input!";
        return 0;
    }

    int mode=selectTrafficMode();

    if(mode<1||mode>3){
        cout<<"Invalid traffic mode!";
        return 0;
    }
    Network network(capacity, b1, b2, b3);
    int packetId=1;
    for(int step=1;step<=steps;step++){
        cout<<"\n\n========== STEP "<<step<<"==========\n";

        int newPackets=generateTraffic(mode, arrivals);
        cout<<"New packets arriving: "<< newPackets << endl;

        // Generate and route packets
        for(int i=0;i<newPackets;i++){
            int size=rand() % 900 + 100;
            Packet p(packetId, size);
            cout<<"\nPacket "<<packetId<< " | Size: " << size << " bytes\n";
            network.routePacket(p);
            packetId++;
        }
        cout<<"\n--- Buffer Status Before Processing ---\n";
        network.showNetworkStatus();

        cout<<"\n--- Processing Packets ---\n";
        network.processAllRouters();

        cout<<"\n--- Buffer Status After Processing ---\n";
        network.showNetworkStatus();
    }

    network.showResults();

    return 0;
}