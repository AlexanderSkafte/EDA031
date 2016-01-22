
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
		auto cmp = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
		auto it = std::find_if(data.begin(), data.end(), cmp);
		if (it != data.end()) {
			data.erase(it);
			return true;
		} else {
			return false;
		}
	}

	/*
	 * Find the IP address for the specified host name. Returns
	 * NON_EXISTING_ADDRESS if the host name wasn't in the name
	 * server.
	 */
	IPAddress lookup(const HostName& h) const
	{
		auto cmp = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
		auto it = std::find_if(data.begin(), data.end(), cmp);
		return (it != data.end()) ? it->second : NON_EXISTING_ADDRESS;
	}

private:
	std::map<HostName, IPAddress> data;
};

#endif

