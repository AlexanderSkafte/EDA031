
#ifndef HNS_HPP
#define HNS_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "nameserverinterface.h"

class HNS : public NameServerInterface {
public:

	HNS(const int size)
		: size_{size}
	{
		data_.reserve(size);
	}

	/*
	 * Insert a name/address pair. Does not check if the name
	 * or address already exists.
	 */
	void insert(const HostName& h, const IPAddress& ip)
	{
		unsigned int index = this->hash(h) % size_;
		auto& b = data_[index];
		auto eq = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
		const auto& it = find_if(b.begin(), b.end(), eq);
		if (it != b.end()) {
			return;
		}
		b.push_back(std::make_pair(h, ip));
	}

	/*
	 * Remove the pair with the specified host name. Returns true
	 * if the host name existed and the pair was removed, false
	 * otherwise.
	 */
	bool remove(const HostName& h)
	{
		unsigned int index = this->hash(h) % size_;
		auto& b = data_[index];
		auto eq = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
		const auto& it = find_if(b.begin(), b.end(), eq);
		if (it != b.end()) {
			b.erase(it);
			return true;
		}
		return false;
	}

	/*
	 * Find the IP address for the specified host name. Returns
	 * NON_EXISTING_ADDRESS if the host name wasn't in the name
	 * server.
	 */
	IPAddress lookup(const HostName& h) const
	{
		unsigned int index = this->hash(h) % size_;
		auto eq = [h](std::pair<HostName, IPAddress> p) { return h == p.first; };
		const auto& b = data_[index];
		const auto& it = std::find_if(b.begin(), b.end(), eq);
		if (it != b.end()) {
			return it->second;
		} else {
			return NON_EXISTING_ADDRESS;
		}
	}

private:
	unsigned int hash(const HostName& h) const
	{
		unsigned int hash = 5381;
		int c, i = 0;

		while ((c = h[i++]) != 0) {
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}

		return hash;
	}

	int size_;
	std::vector<std::vector<std::pair<HostName, IPAddress>>> data_;
};

#endif

