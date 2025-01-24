int fedisableexcept(int excepts) {
	return 0;
}

int feenableexcept(int excepts) {
	if(excepts != 0) {
		return -1;
	}
	return 0;
}

int fegetexcept(void) {
	return 0;
}
