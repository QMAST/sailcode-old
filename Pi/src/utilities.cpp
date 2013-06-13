
static double Utilities::reconcileAngle(double* data, double* confidence, int num) {
	/*
	Takes a list of angles, and a list of confidences in those numbers, 
	and returns the most likely correct angle. Will not work terribly well 
	if it has a bunch of wildly different values with high confidences, 
	but otherwise is effective. Rather computationally intensive -
	may need to be optimized later on.
	*/

	//Note: all the angle math here has to be modular with 360, 
	//to make the angles work properly.

	//First step, generate the PDF. 
	//Treat every data point as a gaussian distribution, scaled by its confidence.
	//Combine these to create a PDF for the actual data point.
	steps = 360/DELTA;

	double* pdf = new double[steps]; //Evaluate the pdf every 5 degrees. can change this later on.
	int x;
	int dif;
	double term;

	double scalingFactor = 1.0/(RT2PI * 10 * num);
	double expectedValue, area;//For computing the centroid.
	expectedValue=0.0;
	area=0.0;


	for(int j=0; j<steps; j++) {//go through all the angles...
		pdf[j]= 0.0; //
		x=0;

		for(int i=0; i<num; i++) {//For every data point
			
			double width = 10.0/confidence[i];
		
			dif = abs(x-((int) data[i]));//find the difference, modulo 360
			if(dif>180) dif=360-dif;
			term = exp(-((dif*dif)/(2*width*width)));
			pdf[j] += confidence[i]*scalingFactor*term;
			
		}

		expectedValue += (DELTA*x*pdf[j]);
		area += (DELTA*pdf[j]);

		x+=DELTA;
	}

	//Now we have a (hopefully correct) which describes the distribution of the values.
	//Our next step is to find the "centroid" of the system. To find the centroid, we need to calculate 2 integrals. 
	//These are calculated in the last loop, the expected value and the area.
	double centroid = expectedValue/area;

	//Now we need to find the area on both side of the centroid. The centroid should be a value from 0-360, corresponding to an x value. 
	//What if it isnt? Is that possible? presumably it is, since the estimation could be overwraught. 
	//If that is the case, just truncate it to the nearest allowable value. 
	int index = (int) centroid/5;
	if(index<0) index = 0;
	if(index>=steps) index=steps-1;
	//Need to find the area of the left-hand side (side up to the centroid) and find the supremum.
	double halfArea =0.0;
	int sup = 0;
	for(int i=0; i<index; i++) {
		halfArea += (DELTA*pdf[i]);
		if(pdf[sup] < pdf[i]) {
			sup = i;
		}
	}

	if(halfArea>(area/2)) {
		
		delete[] pdf;
		return sup*DELTA;//Returns the approximate angle.
	} else {
		sup = index;
		for(int i=index; i<steps; i++) {
			if(pdf[sup] < pdf[i]) {
				sup = i;
			}
		}

		delete[] pdf;
		return sup*DELTA;
	}
}

static double Utilities::reconcileValue(double* data, double* confidence, double deviation,int num) {
	/*
		Same as above, but doesn't deal with angles - doesn't need to worry about the wrap around. 
		Suitable for wind speeds and such things. For this, we also need to find an appropriate max/min.
		Also takes the "standard deviation" as a parameter, just a range around which noise would be expected.
		For example, in the wind speed, we may expect noise to be a couple of km/h in either direction.
		When using this function, tweaking the deviation may be necessary to get a good result.
	*/
	//First things first, need to find top and bottom limits.
	

	steps = 360/DELTA;

	double* pdf = new double[steps]; //Evaluate the pdf every 5 degrees. can change this later on.
	int x;
	int dif;
	double term;

	double scalingFactor = 1.0/(RT2PI * 10 * num);
	double expectedValue, area;//For computing the centroid.
	expectedValue=0.0;
	area=0.0;


	for(int j=0; j<steps; j++) {//go through all the angles...
		pdf[j]= 0.0; //
		x=0;

		for(int i=0; i<num; i++) {//For every data point
			
			double width = 10.0/confidence[i];
		
			dif = abs(x-((int) data[i]));//find the difference, modulo 360
			if(dif>180) dif=360-dif;
			term = exp(-((dif*dif)/(2*width*width)));
			pdf[j] += confidence[i]*scalingFactor*term;
			
		}

		expectedValue += (DELTA*x*pdf[j]);
		area += (DELTA*pdf[j]);

		x+=DELTA;
	}

	//Now we have a (hopefully correct) which describes the distribution of the values.
	//Our next step is to find the "centroid" of the system. To find the centroid, we need to calculate 2 integrals. 
	//These are calculated in the last loop, the expected value and the area.
	double centroid = expectedValue/area;

	//Now we need to find the area on both side of the centroid. The centroid should be a value from 0-360, corresponding to an x value. 
	//What if it isnt? Is that possible? presumably it is, since the estimation could be overwraught. 
	//If that is the case, just truncate it to the nearest allowable value. 
	int index = (int) centroid/5;
	if(index<0) index = 0;
	if(index>=steps) index=steps-1;
	//Need to find the area of the left-hand side (side up to the centroid) and find the supremum.
	double halfArea =0.0;
	int sup = 0;
	for(int i=0; i<index; i++) {
		halfArea += (DELTA*pdf[i]);
		if(pdf[sup] < pdf[i]) {
			sup = i;
		}
	}

	if(halfArea>(area/2)) {
		
		delete[] pdf;
		return sup*DELTA;//Returns the approximate angle.
	} else {
		sup = index;
		for(int i=index; i<steps; i++) {
			if(pdf[sup] < pdf[i]) {
				sup = i;
			}
		}

		delete[] pdf;
		return sup*DELTA;
	}
}