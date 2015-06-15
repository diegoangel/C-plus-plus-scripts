/*
 * An example file showing the usage of the C++ libmemcached interface.
 */
/*#include <mem_config.h>
*/
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>

#include <string.h>

#include <libmemcached/memcached.hpp>

using namespace std;
using namespace memcache;

class DeletePtrs
{
public:
  template<typename T>
  inline void operator()(const T *ptr) const
  {
    delete ptr;
  }
};

class MyCache
{
public:

  static const uint32_t num_of_clients= 10;

  static MyCache &singleton()
  {
    static MyCache instance;
    return instance;
  }

  void set(const string &key,
           const vector<char> &value)
  {
    time_t expiry= 800;
    uint32_t flags= 0;
    getCache()->set(key, value, expiry, flags);
  }

  vector<char> get(const string &key)
  {
    vector<char> ret_value;
    getCache()->get(key, ret_value);
    return ret_value;
  }

  void remove(const string &key)
  {
    getCache()->remove(key);
  }

  Memcache *getCache()
  {
    /* 
     * pick a random element from the vector of clients. Obviously, this is
     * not very random but suffices as an example!
     */
//    uint32_t index= rand() % num_of_clients;
    return client;
  } 

private:

  /*
   * A vector of clients.
   */
  Memcache * client;

  MyCache()
    :
      client()
  {
    /* create clients and add them to the vector */
    //for (uint32_t i= 0; i < num_of_clients; i++)
    //{
      Memcache *client= new Memcache("127.0.0.1:11211");
      //clients.push_back(client);
    //}
  }

  ~MyCache()
  {
    //for_each(clients.begin(), clients.end(), DeletePtrs());
    //clients.clear();
    delete client;
  }

  MyCache(const MyCache&);

};

class Product
{
public:

  Product(int in_id, double in_price)
    :
      id(in_id),
      price(in_price)
  {}

  Product()
    :
      id(0),
      price(0.0)
  {}

  int getId() const
  {
    return id;
  }

  double getPrice() const
  {
    return price;
  }

private:

  int id;
  double price;

};

void setAllProducts(vector<Product> &products)
{
  vector<char> raw_products(products.size() * sizeof(Product));
  memcpy(&raw_products[0], &products[0], products.size() * sizeof(Product));
  MyCache::singleton().set("AllProducts", raw_products);
}

vector<Product> getAllProducts()
{
  vector<char> raw_products = MyCache::singleton().get("AllProducts");
  vector<Product> products(raw_products.size() / sizeof(Product));
  memcpy(&products[0], &raw_products[0], raw_products.size());
  return products;
}

Product getProduct(const string &key)
{
  vector<char> raw_product= MyCache::singleton().get(key);
  Product ret;
  if (! raw_product.empty())
  {
    memcpy(&ret, &raw_product[0], sizeof(Product));
  }
  else  
  {
    cout << "No anda...." << endl;
    /* retrieve it from the persistent store */
  }
  return ret;
}

void setProduct(const string &key, const Product &product)
{
  cout << product.getPrice() << endl;
  vector<char> raw_product(sizeof(Product));
    
  for (std::vector<char>::iterator it = raw_product.begin() ; it != raw_product.end(); ++it)
    cout << " h " << *it;
  cout << "\n";
  
  memcpy(&raw_product[0], &product, sizeof(Product));
  cout << raw_product[0] << endl;
  MyCache::singleton().set(key, raw_product);
}

int main()
{
    cout << "puto" << endl;
  /*Memcache first_client("127.0.0.1:11211");
  map< string, map<string, string> > my_stats;
  cout << "puto" << endl;
  first_client.getStats(my_stats);
  */
    Memcache *client = new Memcache("127.0.0.1:11211");
    vector<char> v;
    //for(int i=0; i < 10; ++i)
    v.push_back('h');
    //v.push_back("e");
    //v.push_back("l");
    //v.push_back("l");
    //v.push_back("o");
    cout << v[0] << endl;
    //for ( char c : v ) std::cout << c;
    client->set("hallo", v, 800, 0);
    cout << client->get("192.168.0.23", v);
//    delete client;
    
  /*
   * Iterate through the retrieved stats.
   */
/*  map< string, map<string, string> >::iterator it=
    my_stats.begin();
  while (it != my_stats.end())
  {
    cout << "working with server: " << (*it).first << endl;
    map<string, string> serv_stats= (*it).second;
    map<string, string>::iterator iter= serv_stats.begin();
    while (iter != serv_stats.end())
    {
      cout << (*iter).first << ":" << (*iter).second << endl;
      ++iter;
    }
    ++it;
  }
*/
  return EXIT_SUCCESS;
}
