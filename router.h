#include<stdlib.h>
#include<string> 
#include<iostream>
#include<list>
#include<unordered_set>
#include "packet.h"

int numOfTransmissions = 0; 

//Router clas
class router{
    
    private: 
        std::string addr;
        std::unordered_set<router*> adjRouters; 
        std::unordered_set<int> seen; 
        static Settings settings;

    public: 
        router(void){
        }

        router(std::string router_addr)
        {
            this->addr = router_addr;
        }

        router& operator = (router& src){
            this->addr = src.addr;
            this->adjRouters = std::unordered_set< router* >(src.adjRouters.begin(), src.adjRouters.end());
            return *this;
        }

        void makeNewConnection(router &destination)
        {
            this->adjRouters.insert(&destination);
            destination.adjRouters.insert(this);
        }
        template <class T>
        void receive(packet<T> pckt)
        {    
            std::string src_ip_addr = pckt.getOrigin();
            if(!settings._allowLooping)
            {
                if(this->seen.find(pckt.getPacketID()) != this->seen.end())
                {
                    std::cout<<"\n";
                    std::cout<<"Status: Discarded (Already Forwarded).\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nFrom: "<<pckt.getOrigin()<<"\nRemaining Hops: "<<pckt.getHops()<<std::endl;
                    std::cout<<"\n";
                    return;
                }
                this->seen.insert(pckt.getPacketID());
            }
            
            if(pckt.getDestIP() == this->getIPaddr())
            {
                std::cout<<"\n";
                std::cout<<"Status: Received\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nFrom: "<<pckt.getOrigin()<<"\nData: "<<pckt.getPayload()<<std::endl;
                std::cout<<"\n"<<std::endl;
                std::cout<<"Resuming Simulation....\n"<<std::endl;               
            }
            else if(pckt.getHops() == 0) 
            {
                std::cout<<"\n";
                std::cout<<"Status: Discarded (Hop Count = 0)\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nFrom: "<<pckt.getOrigin()<<std::endl;
                std::cout<<"\n";
            }
            else 
            {   
                std::cout<<"\n";
                std::cout<<"Status: In transit\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nFrom: "<<pckt.getOrigin()<<"\nRemaining Hops: "<<pckt.getHops()<<std::endl;
                std::cout<<"\n";

                for(auto adjRouter: this->adjRouters)
                    if(adjRouter->getIPaddr() != src_ip_addr)
                        this->send(pckt, adjRouter);
            }

            return;
        }
        
        std::string getIPaddr()
        {
            return this->addr;
        }
 
        template <class T>
        void send(packet<T> pckt, router *destination) 
        {
            numOfTransmissions++; 
            pckt.decHops(); 
            pckt.setOrigin(this->getIPaddr()); 
            destination->receive(pckt);
        }

        ~router(){
        }
};