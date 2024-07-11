using std::exception;

/**
 * Throw this exception when more material is asked than is available
 */
class NotEnoughMaterial : public exception {

	private:
		string msg;

	public:

		NotEnoughMaterial(string msg = "") {
			this->msg = msg;
		}

		string getMsg() {
			return this->msg;
		}

};
