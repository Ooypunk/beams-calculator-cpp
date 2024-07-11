using std::exception;
using std::string;

class HeaderTooSmall : public exception {

	private:
		string error_msg;

	public:

		HeaderTooSmall(string error_msg) {
			this->error_msg = error_msg;
		}

		string getMessage() {
			return this->error_msg;
		}

};
