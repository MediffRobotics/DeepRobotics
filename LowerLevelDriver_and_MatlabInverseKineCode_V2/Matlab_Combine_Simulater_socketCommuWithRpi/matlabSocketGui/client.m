% CLIENT connect to a server and read a ReceivedMessage
%
% Usage - ReceivedMessage = client(host, port, number_of_retries)
function ReceivedMessage = client(host, port, number_of_retries,SendMessage)

    import java.net.Socket
    import java.io.*

    if (nargin < 3)
        number_of_retries = 20; % set to -1 for infinite
    end
    
    retry        = 0;
    input_socket = [];
    ReceivedMessage      = [];

    while true

        retry = retry + 1;
        if ((number_of_retries > 0) && (retry > number_of_retries))
            fprintf(1, 'Too many retries\n');
            break;
        end
        
        try
            fprintf(1, 'Retry %d connecting to %s:%d\n', ...
                    retry, host, port);

            % throws if unable to connect
            input_socket = Socket(host, port);

            % get a buffered data input stream from the socket
            input_stream   = input_socket.getInputStream;
            d_input_stream = DataInputStream(input_stream);

            fprintf(1, 'Connected to server\n');
           
           %% write data to socket (remote hosts)
            Read_output_stream=input_socket.getOutputStream;
            d_Readoutput_stream = DataOutputStream(Read_output_stream);

            % output the data over the DataOutputStream
            % Convert to stream of bytes
            % pause(0.5);            
            fprintf(1, 'Writing %d bytes\n', length(SendMessage));
            d_Readoutput_stream.writeBytes(char(SendMessage));
            d_Readoutput_stream.flush;

           %%  read data from the socket(remote hosts) - wait a short time first
            pause(0.5);
            bytes_available = input_stream.available;
            fprintf(1, 'Reading %d bytes\n', bytes_available);
            
            ReceivedMessage = zeros(1, bytes_available, 'uint8');
            for i = 1:bytes_available
                ReceivedMessage(i) = d_input_stream.readByte;
            end
            
            ReceivedMessage = char(ReceivedMessage);
            
            % cleanup
            input_socket.close;
            break;
            
        catch
            if ~isempty(input_socket)
                input_socket.close;
            end

            % pause before retrying
            pause(1);
        end
    end
end