//
// SVGeocoder.h
//
// Created by Sam Vermette on 07.02.11.
// Copyright 2011 samvermette.com. All rights reserved.
//
// https://github.com/samvermette/SVGeocoder
// http://code.google.com/apis/maps/documentation/geocoding/
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>

#import "SVPlacemark.h"

typedef enum {
	SVGeocoderZeroResultsError = 1,
	SVGeocoderOverQueryLimitError,
	SVGeocoderRequestDeniedError,
	SVGeocoderInvalidRequestError,
    SVGeocoderJSONParsingError
} SVGecoderError;


typedef void (^SVGeocoderCompletionHandler)(NSArray *placemarks, NSHTTPURLResponse *urlResponse, NSError *error);

@interface SVGeocoder : NSOperation

+ (SVGeocoder*)geocode:(NSString *)address completion:(SVGeocoderCompletionHandler)block;
+ (SVGeocoder*)geocode:(NSString *)address bounds:(MKCoordinateRegion)bounds completion:(SVGeocoderCompletionHandler)block;
+ (SVGeocoder*)geocode:(NSString *)address region:(NSString *)regionString completion:(SVGeocoderCompletionHandler)block;

+ (SVGeocoder*)reverseGeocode:(CLLocationCoordinate2D)coordinate completion:(SVGeocoderCompletionHandler)block;

- (SVGeocoder*)initWithAddress:(NSString *)address completion:(SVGeocoderCompletionHandler)block;
- (SVGeocoder*)initWithAddress:(NSString *)address bounds:(MKCoordinateRegion)bounds completion:(SVGeocoderCompletionHandler)block;
- (SVGeocoder*)initWithAddress:(NSString *)address region:(NSString *)regionString completion:(SVGeocoderCompletionHandler)block;

- (SVGeocoder*)initWithCoordinate:(CLLocationCoordinate2D)coordinate completion:(SVGeocoderCompletionHandler)block;

@optional
- (void)geocoder:(SVGeocoder *)geocoder didFindPlacemark:(SVPlacemark *)placemark; // SVPlacemark is an MKPlacemark subclass with a coordinate property
- (void)geocoder:(SVGeocoder *)geocoder didFindPlacemarks:(NSArray *)placemarks; // array of SVPlacemark objects
- (void)geocoder:(SVGeocoder *)geocoder didFindPlacemarksRaw:(NSArray *)placemarks; // array of SVPlacemark raw data
- (void)geocoder:(SVGeocoder *)geocoder didFailWithError:(NSError *)error;
- (void)start;
- (void)cancel;

@end
