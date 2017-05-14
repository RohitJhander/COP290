#include "Connection.hpp"
#include <iostream>

Connection::Connection() {
	mode = None;
	numberOfPeers = 0;
	counter = 0;
	reliability = 5;
	protocolID = 123456;
	waitingTime = 0.03;
	DISCONNECT = 120;
	socket.setBlocking(false);
	ip = sf::IpAddress::getLocalAddress();
	std::cout<<"My IP = "<<ip<<std::endl;
	port = 4000;
	if(socket.bind(port) != sf::Socket::Done) {
		std::cout<<"Constructor: Error on binding to port "<<port<<std::endl;
		exit(0);
	}else{
		std::cout<<"My port = "<<port<<std::endl;
	}
}

Connection::~Connection() {}

void Connection::changeMode(Mode m) {
	mode = m;
}

Mode Connection::getMode() {
	return this->mode;
}

int Connection::getNumberOfPeers() {
	return numberOfPeers;
}

void Connection::accept(int& n, sf::IpAddress& senderIP) {
	sf::Packet packet;
	unsigned short senderPort;
	while(true){
		if(socket.receive(packet,senderIP,senderPort) != sf::Socket::Done) {
			//std::cout<<"Error receiving packet \n";
		}else{
			if(!checkPacket(packet)){
				continue;
			}
			int msg;
			packet>>msg>>n;
			if(msg != 10001){
				#ifdef PRINT
					std::cout<<"msg not equal to 10001"<<std::endl;
				#endif
				continue;
			}

			std::cout<<"JOIN request from "<<senderIP.toString()<<" on port "<<senderPort<<" with teamNumber "<<n<<std::endl;
			if(portMap.find(senderIP) == portMap.end()) {
				portMap[senderIP] = senderPort;
				teamMap[senderIP] = n;
				numberOfPeers++;
			}
			break;
		}
	}
}

void Connection::send() {
	while(outQ.empty() == false){
		for(auto it = portMap.begin() ; it != portMap.end() ; ++it) {
			for(int i=0 ; i<reliability; i++) {
				if(socket.send(outQ.front(),(*it).first,(*it).second) != sf::Socket::Done){
					//std::cout<<"Error sending packet to "<<((*it).first).toString()<<" on port "<<(*it).second<<std::endl;
				}else{
					//std::cout<<"packet sent successfully to "<<((*it).first).toString()<<" on port "<<(*it).second<<std::endl;
				}
			}
		}
		outQ.pop();
	}
	if(counter > 1000){
		counter = 0;
	}
}

void Connection::receive() {
	sf::Packet packet;
	sf::IpAddress senderIP;
	unsigned short senderPort;
	while(true){
		if(connectionTimer.getElapsedTime() > (sf::seconds(waitingTime))) {
			connectionTimer.restart();
			break;
		}
		if(socket.receive(packet,senderIP,senderPort) != sf::Socket::Done) {
			//std::cout<<"Error receiving packet \n";
		}else{
			if(!checkPacket(packet)){
				return;
			}
			int count;
			packet>>count;
			inQ[senderIP][count] = packet;	
		}
	}
	for(auto it = inQ.begin(); it != inQ.end(); ++it){
		if(it->second.size() == 0){
			statusMap[it->first]++;
			if(statusMap[it->first] > DISCONNECT){
				inQ.erase(it);
				teamMap.erase(it->first);
				statusMap.erase(it->first);
				disconnectedUsers.push(it->first);
				#ifdef PRINT
					std::cout<<"player removed, ip : "<<it->first.toString()<<std::endl;
				#endif
			}
		}else{
			statusMap[it->first] = 0;
		}
	}
}

void Connection::addPeer(sf::IpAddress ip, unsigned short port, int n) {
	portMap[ip] = port;
	teamMap[ip] = n;
	statusMap[ip] = 0;
}

void Connection::addToOutQ(sf::Packet packet) {
	outQ.push(packet);
}

std::map< sf::IpAddress, std::map< int, sf::Packet > >& Connection::getInQ() {
	return inQ;
}

void Connection::sendJoinRequest(int teamNumber) {
	sf::Packet packet;
	packet<<protocolID;
	int msg = 10001;
	packet<<msg<<teamNumber;
	socket.send(packet, portMap.begin()->first, portMap.begin()->second);
}

void Connection::sendStartCommand() {
	sf::Packet packet;
	packet<<protocolID;
	int msg = 30001;
	packet<<msg;
	addToOutQ(packet);
	send();
}

void Connection::receiveStartCommand() {
	sf::Packet packet;
	sf::IpAddress senderIP;
	unsigned short senderPort;
	while(true){
		if(socket.receive(packet,senderIP,senderPort) != sf::Socket::Done) {
			//std::cout<<"Error receiving packet \n";
		}else{
			#ifdef PRINT
				std::cout<<"Packet arrived"<<std::endl;
			#endif
			if(!checkPacket(packet)){
				continue;
			}
			int msg;
			packet>>msg;
			if(msg == 30001){
				#ifdef PRINT
					std::cout<<"msg equal to 30001"<<std::endl;
				#endif
				break;
			}else{
				#ifdef PRINT
					std::cout<<"msg not equal to 30001"<<std::endl;
				#endif
			}
		}
	}
}

bool Connection::checkPacket(sf::Packet& packet) {
	int ID;
	if(packet>>ID){
		if(ID != protocolID){
			#ifdef PRINT
				std::cout<<"wrong protocolID "<<ID<<std::endl;
			#endif
			return false;
		}
		return true;
	}else{
		#ifdef PRINT
			std::cout<<"Error reading ID from packet"<<std::endl;
		#endif
		return false;
	}
}

void Connection::establishP2P(){
	if (mode == Host){
		//send ips to all clients
		sf::Packet packet;
		packet<<protocolID;
		int size = portMap.size();
		packet<<size;
		auto itt = teamMap.begin();
		auto itp = portMap.begin();
		while(itt != teamMap.end()){
			packet<<(itt->first).toString()<<(itt->second)<<itp->second;
			++itt;
			++itp;
		}
		for (auto it = portMap.begin(); it != portMap.end(); ++it){
			socket.send(packet, it->first, it->second);
			#ifdef PRINT
				std::cout<<"sending ip"<<std::endl;
			#endif
		}
	} else /*mode == Client*/ {
		//recieve ips of all other players
		sf::Packet packet;
		sf::IpAddress senderIP;
		unsigned short senderPort;
		while(true){
			if(socket.receive(packet,senderIP,senderPort) != sf::Socket::Done) {
				//std::cout<<"Error receiving packet \n";
			} else {
				if(!checkPacket(packet)){
					continue;
				}
				int size;
				sf::IpAddress IP;
				std::string ipstr;
				unsigned short int Port;
				int team;
				packet>>size;
				for(int i=0 ; i<size; i++){
					packet>>ipstr;
					std::cout<<ipstr<<std::endl;
					IP = sf::IpAddress(ipstr);
					packet>>team;
					packet>>Port;
					if(IP != sf::IpAddress::getLocalAddress()){
						addPeer(IP,Port,team);
					}
				}
				break;
			}
		}
	}
}


std::map< sf::IpAddress , int >& Connection::getTeamMap() {
	return teamMap;
}

std::queue<sf::IpAddress>& Connection::getDeadConnection(){
	return disconnectedUsers;
}
