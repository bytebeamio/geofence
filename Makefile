test: test.c geofence.h geofence.c
	gcc test.c geofence.c -o test
	./test

clean:
	rm -f test