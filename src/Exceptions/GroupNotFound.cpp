using std::exception;
using std::string;

class GroupNotFound : public exception {

	private:
		string error_msg;

	public:

		GroupNotFound(string error_msg) {
			this->error_msg = error_msg;
		}

		string getMessage() {
			return this->error_msg;
		}

};
