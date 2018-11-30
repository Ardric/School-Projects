
#include "Socket.h"

Socket::Socket(){
    host = "";
    port = "";
    closed = true;
    set = NULL;
}


void Socket::joinGroup(SocketSet* grp){
    if(set != NULL)
        set->leave(fd);
    set = grp;
    if(set != NULL)
        set->join(fd);
}

void Socket::leaveGroup(){
    if(set != NULL){
        set->leave(fd);
    }
    set = NULL;
}

bool Socket::hasEvent(){
    if(set == NULL)
        return false;
    return set->isSet(fd);
}

//need to add error detection
void Socket::open(string hosto,string porto){
	struct addrinfo hints;
    struct addrinfo *info;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(hosto.c_str(), porto.c_str(), &hints,  &info);
    fd = socket(info->ai_family, info->ai_socktype, 0);
    int result = connect(fd, info->ai_addr, info->ai_addrlen);

    result++;
    
    host = hosto;
    port = porto;
    
    freeaddrinfo(info);
    closed = false;
}

//need to add error detection
void Socket::listen(string porto){
  
    struct addrinfo hints;
    struct addrinfo *info;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // or use AF_UNSPEC
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(NULL, porto.c_str(), &hints, &info);
    
    port = porto;
    
    
    //This is the socket that will listen for connections
    fd = socket(info->ai_family, info->ai_socktype, 0);
    
    int error = bind(fd, info->ai_addr, info->ai_addrlen);
    
    freeaddrinfo(info);
    
    error = ::listen(fd,4);

    if (error < 0) {
        closed = true;
    }else{
        closed = false;
    }
}

Socket Socket::accept(){
    Socket sock;
    
    struct sockaddr_storage address;
    socklen_t size = sizeof(address);
    bzero(&address, sizeof(address));
    
    sock.fd = ::accept(fd, (struct sockaddr *)&address, &size);
    
    char ip[NI_MAXHOST];
    char srv[NI_MAXSERV];
    
    getnameinfo(((sockaddr *)&address), size, ip, sizeof(ip),srv, sizeof(srv), NI_NUMERICHOST | NI_NUMERICSERV);
    
    sock.host = ip;
    sock.port = srv;
    sock.closed = false;
    return sock;
    
}

int Socket::write(unsigned char* buf,int size){
    if(closed)
        return -1;
    
    int bytes = ::write(fd,buf,size*sizeof(unsigned char));
    if(bytes <= 0){
        close();
    }
    return bytes;
}

int Socket::writeInt(int a){
	return write((unsigned char*)&a,sizeof(int));
}

int Socket::writeDouble(int d){
	return write((unsigned char*)&d,sizeof(double));
}

int Socket::writeString(string str){
	return write((unsigned char*)str.c_str(),str.size());
}

int Socket::read(unsigned char* buf,int size){
    if(closed){
        return -1;
    }
	int bytes = ::read(fd,buf,size);
    if(bytes <= 0){
        close();
    }
    return bytes;
}

int Socket::readInt(int* a){
	return read((unsigned char*)a,sizeof(int));
}

int Socket::readString(string& buf,int size){
	if(size < 0 || size > 1024)
		return -1;
	int bytes = read(&buffer[0],size);
	buf = "";
	if(bytes >= 0){
		buffer[bytes] = 0;
		buf = string((char *)buffer);
	}
	return bytes;
}

int Socket::readDouble(double* d){
	return read((unsigned char*)d,sizeof(d));
}

void Socket::close(){
    closed = true;
    ::close(fd);
    leaveGroup();
}

bool Socket::isClosed(){
    return closed;
}

string Socket::toString(){
    stringstream str;
    str << host << ":" << port << " " << fd;
    
    return str.str();
    
}

