using std::exception;
using std::string;

class HeaderNotFound : public exception {

	private:
		string error_msg;

	public:

		HeaderNotFound(string error_msg) {
			this->error_msg = error_msg;
		}

		string getMessage() {
			return this->error_msg;
		}

};
