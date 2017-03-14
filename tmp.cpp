int tmp () {

	int x;

  #pragma omp parallel for
	for (int i = 0; i < 10; i++) {
		  x = i;
	}

	return 0;
}
