from flask import Flask , url_for , request , g , send_from_directory , render_template
import random , py_mouse_key

# --------------------------------------------------------

def dump_request_detail ( request ):

    request_detail = 'request.method = GET, so skip request detail'

    if request.method and request.method == 'POST':

        request_detail = """ # Before Request # \n headers: {request.headers} """

    return request_detail.format ( request = request ).strip ()

# --------------------------------------------------------

app = Flask ( __name__ , static_folder=None , template_folder='template' )

@app.route ( '/static/<path:filename>' )
def assets ( filename ):
    return send_from_directory ( 'static' , filename )

# --------------------------------------------------------

@app.before_request
def callme_before_every_request():
    app.logger.debug('\n\n')
    id_g = ''
    for i in range ( 9 ): id_g += str ( random.randint(0, 9) )
    app.logger.debug('Before request id: {}'.format(id_g))
    app.logger.debug(dump_request_detail(request))
    g.id_g = id_g

@app.after_request
def callme_after_every_response(response):

    app.logger.debug('After  request id: {g.id_g}'.format(g=g))

    if request.method and request.method == 'POST':

        app.logger.debug('After Request #\n' + repr(response))

    else: app.logger.debug('request.method = GET, so skip response detail' )

    app.logger.debug('\n\n')
    return response

# --------------------------------------------------------

@app.route ( '/' , methods=['GET'] )
def basic ():
    app.logger.debug ( 'switch to index.' )
    return render_template ( 'index.html' )
    
# --------------------------------------------------------

@app.route ( '/numbers/' , methods=['POST'] )
def numbers_response ():
    app.logger.debug ( 'switch to py_mouse_key.' )
    return str ( py_mouse_key.hack ( app , request ) )

# --------------------------------------------------------

@app.route ( '/<path:default>/' , methods=['GET' , 'POST'] )
def regex_impact ( default ):
    app.logger.debug ( 'switch to default.' )
    return ''

# --------------------------------------------------------

if __name__ == "__main__": app.run( '0.0.0.0' , port=8088 , debug=True )
