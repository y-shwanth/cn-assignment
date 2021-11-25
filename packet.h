#include "settings.h"
#include <string>
int packetIDseq = 0;

//Packet class
template <class T>
class packet{
    private: 

        int packet_id;
        int hops; 
        T payload; 
        Settings settings; 
        std::string origin; 
        std::string destination_IP; 
    
    public: 
        packet(void)
        {
            this->hops = settings._defaultHopCount;
            packet_id = packetIDseq++;
        }
        packet(T &payLoad, std::string dest_ip_addr)
        {
            this->hops = settings._defaultHopCount;
            packet_id = packetIDseq++;
            payload = payLoad;
            destination_IP = dest_ip_addr;
        }
        packet& operator = (packet& src)
        {
            this->hops = src.hops;
            this->packet_id = src.packet_id;
            this->payload = src.payload;
            this->destination_IP = src.destination_IP;
            return *this;
        }

        int getHops()
        {
            return hops;
        }

        void setHops(int newHops)
        {
            this->hops = newHops;
        }

        void decHops()
        {
            hops--;
        }

        void incHops()
        {
            hops++;
        }

        void setPayload(T srcPayload)
        {
            this->payload = srcPayload;
        }

        void setOrigin(std::string origin)
        {
            this->origin = origin;
        }

        void setDestIP(std::string dest_ip_addr)
        {
            this->destination_IP = dest_ip_addr;
        }

        T getPayload()
        {
            return payload;
        }
        
        int getPacketID()
        {
            return this->packet_id;
        }
        
        std::string getOrigin()
        {
            return this->origin;
        }

        std::string getDestIP()
        {
            return this->destination_IP;
        }

        ~packet(void){
        }
};