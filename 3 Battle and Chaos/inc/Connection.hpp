/**
 * \class
 * This class manage p2p model used in the game.
 * 
 */


#ifndef Connection_HPP
#define Connection_HPP

#include <SFML/Network.hpp>
#include <map>
#include <queue>

enum Mode {None,Host,Client};
///Generic class for networking. 
class Connection {
private:
	sf::UdpSocket socket;
	sf::IpAddress ip;
	unsigned short port;
	Mode mode;
	int numberOfPeers;
	int reliability;
	float waitingTime;
	int DISCONNECT;
	sf::Clock connectionTimer;

	std::map< sf::IpAddress , int > statusMap;
	std::queue<sf::IpAddress> disconnectedUsers;

	std::map< sf::IpAddress , unsigned short > portMap;
	std::map< sf::IpAddress , int > teamMap;

	std::queue< sf::Packet > outQ;
	std::map< sf::IpAddress, std::map< int, sf::Packet > > inQ;

protected:
	unsigned int protocolID;
	int counter;
public:
	Connection();
	~Connection();

	void changeMode(Mode m);
	Mode getMode();
	int getNumberOfPeers();

	void accept(int&, sf::IpAddress&); ///<Accept new connections from other players.
	void send();
	void receive();
	void addPeer(sf::IpAddress ip, unsigned short port, int n);

	void addToOutQ(sf::Packet packet);
	std::map< sf::IpAddress, std::map< int, sf::Packet > >& getInQ();
	std::queue<sf::IpAddress>& getDeadConnection();

	void sendJoinRequest(int);
	void sendStartCommand();
	void receiveStartCommand();
	bool checkPacket(sf::Packet& packet);

	void establishP2P(); ///<Establish peer to peer connection just before going to main stage
	std::map< sf::IpAddress , int >& getTeamMap();

};

#endif // Connection_HPP