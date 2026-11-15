
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