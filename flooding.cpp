#include<bits/stdc++.h>
#include "router.h"

void makeAndrun()
{
    std::vector<router> routers;
    int numRouters; 
    std::cin>>numRouters;
    std::unordered_map<std::string, int> addr_idx_map;
    
    for(int i = 0; i < numRouters; i++)
    {
        std::string ip_addr;
        std::cin>>ip_addr;
        addr_idx_map[ip_addr] = i;
        routers.push_back(router(ip_addr));
    }
    
    int numEdges; 
    std::cin>>numEdges;

    while(numEdges--)
    {
        std::string addr1, addr2;
        std::cin>>addr1;
        std::cin>>addr2;

        int u = addr_idx_map[addr1]; 
        int v = addr_idx_map[addr2];
        routers[u].makeNewConnection(routers[v]);
    }

    int numPackets;
    std::cin>>numPackets;

    std::vector<packet<std::string>> packets(numPackets);
    for(int i = 0; i < numPackets; i++)
    {
        packet<std::string> pckt;
        pckt.setOrigin("Host");
        
        std::string payload;
        std::getline(std::cin >> std:: ws, payload);
        pckt.setPayload(payload);

        std::string dest_ip;
        std::getline(std::cin >> std::ws, dest_ip);
        pckt.setDestIP(dest_ip);

        packets[i] = pckt;
    }
    std::string src_ip;
    std::cin>>src_ip;

    int src = addr_idx_map[src_ip];
    for(auto &pckt: packets)
        routers[src].receive(pckt);
    return;
}
int main()
{
    freopen("inputfile.in", "r", stdin);
    std::cout<<"Flooding Routing Algorithm (With-out looping)"<<std::endl;
    extern int numOfTransmissions;
    
    makeAndrun();
    std::cout<<std::endl;
    std::cout<<"Simulation is Over!! "<<std::endl;
    std::cout<<"Total number of transmissions : "<<numOfTransmissions<<std::endl;
    return 1;
}
