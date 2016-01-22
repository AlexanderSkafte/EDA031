
#ifndef HNS_HPP
#define HNS_HPP

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <utility>

#include "nameserverinterface.h"

// TODO
//		Needs to be implemented.

class HNS : public NameServerInterface {
public:

	HNS(const int size)
	{
		this->size = size;
	}

	/*
	 * Insert a name/address pair. Does not check if the name
	 * or address already exists.
	 */
	void insert(const HostName& h, const IPAddress& ip)
	{
//		data.insert((std::make_pair(h, ip)));
	}

	/*
	 * Remove the pair with the specified host name. Returns true
	 * if the host name existed and the pair was removed, false
	 * otherwise.
	 */
	bool remove(const HostName& h)
	{
//		auto cmp = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
//		auto it = std::find_if(data.begin(), data.end(), cmp);
//		if (it != data.end()) {
//			data.erase(it);
//			return true;
//		} else {
//			return false;
//		}
	}

	/*
	 * Find the IP address for the specified host name. Returns
	 * NON_EXISTING_ADDRESS if the host name wasn't in the name
	 * server.
	 */
	IPAddress lookup(const HostName& h) const
	{
//		auto cmp = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
//		auto it = std::find_if(data.begin(), data.end(), cmp);
//		return (it != data.end()) ? it->second : NON_EXISTING_ADDRESS;
	}

private:
	unsigned int hash(const HostName& h)
	{
//		unsigned int hash = 5381;
//		int i = 0;
//		while (str[i] != 0) {
//			hash = ((hash << 5) + hash) + str[i++];
//		}
//		return hash % size;
	}	

	const int size;
	std::vector<std::vector<std::pair<HostName, IPAddress>>> data;
};

#endif

