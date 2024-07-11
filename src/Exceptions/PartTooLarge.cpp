using std::exception;

/**
 * Throw this exception when a part is found that doesn't fit in any of the
 * available material
 */
class PartTooLarge : public exception {
};
