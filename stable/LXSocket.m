//
//  EXPersistentObject.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "LXSocket.h"
#import <sys/socket.h>
#import <sys/types.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <netdb.h>
#import <unistd.h>

@implementation LXSocket

+ (id)socket {
	return [[[LXSocket alloc] init] autorelease];
}

- (id)initWithCSocket:(SOCKET)_socket {
	if ((self = [super init])) {
		m_socket = _socket;
	}
	return self;
}

- (id)init {
	if ((self = [super init])) {
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
	}
	return self;
}

- (BOOL)bindToPort:(unsigned)port {
	struct sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(port);
	if (bind(m_socket, (struct sockaddr *) &service, sizeof(service)) == -1) {
		NSLog(@"bind() failed -- %s\n", strerror(errno));
		close(m_socket);
		return NO;
	} else return YES;
}

- (BOOL)listen:(unsigned)limit {
	if (listen(m_socket, limit) == -1) {
		printf("listen(): Error listening on socket\n");
		return NO;
	} else return YES;
}

- (LXSocket*)accept {
	SOCKET AcceptSocket;
	while (YES) {
		AcceptSocket = -1;
		while (AcceptSocket == -1) {
			AcceptSocket = accept(m_socket, NULL, NULL);
		}
		//printf("Server: Client Connected!\n");
		//m_socket = AcceptSocket; 
		return [[LXSocket alloc] initWithCSocket: AcceptSocket];
	}
	return nil;
}

- (BOOL)connect:(NSString*)host port:(unsigned)port {
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr([host UTF8String]);
    clientService.sin_port = htons(port);
    if (connect(m_socket, (struct sockaddr *) &clientService, sizeof(clientService)) == -1) {
        printf("Client: connect() - Failed to connect.\n");
		[activeHost release];
		activeHost = nil;
		return NO;
    } else {
		if (activeHost != host) {
			[activeHost release];
			activeHost = [host retain];
		}
		activePort = port;
		return YES;
	}
}

- (BOOL)sendBytes:(const void*)bytes length:(unsigned)len {
	int sent = send(m_socket, bytes, len, 0);
	return sent == len;
}

- (void*)readBytesWithLength:(unsigned)len {
	void* buffer = malloc(len);
	int received = recv(m_socket, buffer, len, 0);
	if (received <= 0) {
		free(buffer);
		return NULL;
	}
	if (received < len) {
		unsigned remaining = len;
		char* ptr = buffer;
		do {
			remaining -= received;
			ptr += received;
			received = recv(m_socket, ptr, remaining, 0);
			if (received <= 0) {
				free(buffer);
				return NULL;
			}
		} while (received < remaining);
	}
	return buffer;
}

- (BOOL)sendData:(NSData*)data {
	const void* ptr = [data bytes];
	BOOL succeeded = NO;
	if ([self sendInt: [data length]])
		if ([self sendBytes: ptr length: [data length]]) succeeded = YES;
	//free(ptr);
	return succeeded;
}

- (NSData*)readData{
	unsigned len = [self readInt];
	if (len > 0) {
		void* ptr = [self readBytesWithLength: len];
		if (ptr != NULL) {
			NSData* data = [NSData dataWithBytes: ptr length: len];
			free(ptr);
			return data;
		}
	}
	return nil;
}

- (BOOL)sendObject:(id)object {
	NSMutableData* data = [[NSMutableData alloc] init];
	NSKeyedArchiver* archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData: data];
	[archiver encodeRootObject: object];
	[archiver finishEncoding];
	BOOL succeeded = [self sendData: data];
	[archiver release];
	[data release];
	return succeeded;
}

- (id)readObject {
	NSData* data = [self readData];
	if (data != nil) {
		NSKeyedUnarchiver* unarchiver = [[NSKeyedUnarchiver alloc] initForReadingWithData: data];
		id object = [[[unarchiver decodeObject] retain] autorelease];
		[unarchiver release];
		return object;
	}
	return nil;
}

- (BOOL)sendInt:(int)n {
	return [self sendBytes: &n length: sizeof(n)];
}

- (BOOL)sendDouble:(double)n {
	return [self sendBytes: &n length: sizeof(n)];
}

- (BOOL)sendInt64:(long long)n {
	return [self sendBytes: &n length: sizeof(n)];
}

- (int)readInt {
	void* buffer = [self readBytesWithLength: sizeof(int)];
	if (buffer == NULL) return 0;
	int n;
	memcpy(&n, buffer, sizeof(n));
	free(buffer);
	return n;
}

- (double)readDouble {
	void* buffer = [self readBytesWithLength: sizeof(double)];
	if (buffer == NULL) return 0;
	double n;
	memcpy(&n, buffer, sizeof(n));
	free(buffer);
	return n;
}

- (long long)readInt64 {
	void* buffer = [self readBytesWithLength: sizeof(long long)];
	if (buffer == NULL) return 0;
	long long n;
	memcpy(&n, buffer, sizeof(n));
	free(buffer);
	return n;
}

- (BOOL)sendShort:(short)n {
	return [self sendBytes: &n length: sizeof(n)];
}

- (short)readShort {
	void* buffer = [self readBytesWithLength: sizeof(short)];
	if (buffer == NULL) return 0;
	short n;
	memcpy(&n, buffer, sizeof(n));
	free(buffer);
	return n;
}

- (BOOL)sendLong:(long)n {
	return [self sendBytes: &n length: sizeof(n)];
}

- (long)readLong {
	void* buffer = [self readBytesWithLength: sizeof(long)];
	if (buffer == NULL) return 0;
	long n;
	memcpy(&n, buffer, sizeof(n));
	free(buffer);
	return n;
}

- (void)sendString:(NSString*)string {
	const char* s = [string UTF8String];
	int len = strlen(s);
	[self sendInt: len];
	[self sendBytes: s length: len + 1];
}

- (NSString*)readString {
	int len = [self readInt];
	char* s = [self readBytesWithLength: len + 1];
	NSString* string = [NSString stringWithUTF8String: s];
	free(s);
	return string;
}

+ (NSString*)resolveHostName:(NSString*)hostName {
	LXSocket* socket = [[LXSocket alloc] init];
	NSString* ip = [socket resolveHostName: hostName];
	[socket release];
	return ip;
}

- (NSString*)resolveHostName:(NSString*)hostName {
	struct hostent* host = gethostbyname([hostName UTF8String]);
	if (host == NULL) {
		printf("Error resolving host name: %s\n", strerror(errno));
		return nil;
	} else {
		struct in_addr* addr = (struct in_addr*) host->h_addr_list[0];
		char* ip = inet_ntoa(*addr);
		return [NSString stringWithUTF8String: ip];
	}
}

- (NSString*)host {
	return activeHost;
}

- (int)port {
	return activePort;
}

- (void)dealloc {
	[activeHost release];
	close(m_socket);
	[super dealloc];
}

@end
