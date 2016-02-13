
#ifndef MNS_HPP
#define MNS_HPP

#include <algorithm>
#include <functional>
#include <map>
#include <utility>

#include "nameserverinterface.h"

class MNS : public NameServerInterface {
public:

	/*
	 * Insert a name/address pair. Does not check if the name
	 * or address already exists.
	 */
	void insert(const HostName& h, const IPAddress& ip)
	{
		data.insert((std::make_pair(h, ip)));
	}

	/*
	 * Remove the pair with the specified host name. Returns true
	 * if the host name existed and the pair was removed, false
	 * otherwise.
	 */
	bool remove(const HostName& h)
	{
		return data.erase(h);
	}

	/*
	 * Find the IP address for the specified host name. Returns
	 * NON_EXISTING_ADDRESS if the host name wasn't in the name
	 * server.
	 */
	IPAddress lookup(const HostName& h) const
	{
		auto it = data.find(h);
		return (it != data.end()) ? it->second : NON_EXISTING_ADDRESS;
	}

private:
	std::map<HostName, IPAddress> data;
};

#endif

