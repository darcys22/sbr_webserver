#include <iostream>
#include "crow.h"
#include "div.h"

using namespace std;

int main(){

	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([](){
			return "Pong";
	});

	CROW_ROUTE(app, "/add_json")
		.methods("POST"_method)
		([](const crow::request& req){
			auto x = crow::json::load(req.body);
			if (!x)
					return crow::response(400);
			int sum = x["a"].i()+x["b"].i();
			std::ostringstream os;
			os << sum;
			return crow::response{os.str()};
	});

	app.port(18080).multithreaded().run();

  //int x; cin >> x;
  //int y; cin >> y;

  //int quotient = division(x,y);
  //cout << quotient;
  return 0;
}
