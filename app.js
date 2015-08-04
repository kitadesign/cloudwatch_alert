var _            = require( 'underscore' ),
	http         = require( 'http' ),
	AWS          = require( 'aws-sdk' ),
	express      = require( 'express' ),
	logger       = require( 'morgan' ),
	bodyParser   = require( 'body-parser' ),
	cookieParser = require( 'cookie-parser' );

AWS.config.loadFromPath( process.env.NODE_AWS_JSON_PATH );

var app = express();

app.set( 'port', process.env.NODE_PORT || '3000' );
app.use( logger( 'dev' ) );
app.use( bodyParser.json() );
app.use( bodyParser.urlencoded( { extended: false } ) );
app.use( cookieParser() );

app.get( '/', function ( req, res ) {
	( new AWS.CloudWatch() ).describeAlarms( {}, function ( err, data ) {
		var alert = !_.every( data.MetricAlarms, function ( row ) {
			return row.StateValue === 'OK';
		} );
		if ( alert ) return res.send( 500 );
		res.send( 200 );
	} );
} );

http.createServer( app ).listen( app.get( 'port' ) );
