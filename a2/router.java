import java.io.BufferedWriter;
import java.io.FileWriter;
import java.net.*;
import java.nio.*;
import java.util.*;


public class router {
	private int router_id,nse_port,router_port;
	private InetAddress nse_host;
	private DatagramSocket socket;
	private HashMap<Integer, RIB> RIB_list;
	private HashMap<Integer,Topology> Topology_list;
	private HashMap<Integer,Neighbour> neighbours;
	private FileWriter logWriter;
	private BufferedWriter logBuffer;
	
	public router(int id, int port,int router_port, InetAddress nse_host) throws Exception{
		this.router_id = id;
		this.nse_port = port;
		this.nse_host = nse_host;
		this.router_port = router_port;
		this.socket = new DatagramSocket(port);
		RIB_list = new HashMap<Integer, RIB>();
		Topology_list = new HashMap<Integer, Topology>();
		neighbours = new HashMap<Integer, Neighbour>();
	}
	
	public int getID(){
		return this.router_id;
	}
	
    public void sendInitPacket() throws Exception {
        ByteBuffer buffer = ByteBuffer.allocate(4);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.putInt(router_id);
        byte[] sendData = buffer.array();
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, nse_host, nse_port);
        this.socket.send(sendPacket);
        logBuffer.write("R"+router_id+" sends the INIT packet.");
        logBuffer.newLine();
        logBuffer.flush();
        logWriter.flush();
    }

    
    /* Helper function to send the hello packet through related link of
    current router with the circuit database information
 */
 public void sendHelloPacket(Topology topology) throws Exception {
     for (Link link : topology.getLinkTable()) {
         ByteBuffer buffer = ByteBuffer.allocate(8);
         buffer.order(ByteOrder.LITTLE_ENDIAN);
         buffer.putInt(router_id);
         buffer.putInt(link.getID());
         byte[] sendData = buffer.array();
         DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, nse_host, nse_port);
         socket.send(sendPacket);
         logBuffer.write("R"+router_id+" sends a Hello packet: router_id "+router_id+", link_id "+link.getID());
         logBuffer.newLine();
         logBuffer.flush();
         logWriter.flush();
     }
 }
 
    /* Helper function to receive the circuit database from NSE */
    public void receiveCircuitDatabase() throws Exception {
        byte[] receiveData = new byte[512];
        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
        socket.receive(receivePacket);
        logBuffer.write("R"+router_id+" receives a circuit_DB.");
        logBuffer.newLine();
        logBuffer.flush();
        logWriter.flush();
        byte[] CDdata = receivePacket.getData();
        ByteBuffer buffer = ByteBuffer.wrap(CDdata);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        int nbr_link = buffer.getInt();
        /* Add current router's information to the RIB table and also topology table */
        RIB_list.put(router_id,new RIB(router_id,router_id,0));
        Topology topology = new Topology(router_id, router_id);

        /* According to the nbr_link to get all the related links information of current router */
        for (int i = 0; i < nbr_link; i++) {
            int link_id = buffer.getInt();
            int link_cost = buffer.getInt();
            Neighbour neighbour = new Neighbour(link_id, link_cost);
            neighbours.put(link_id, neighbour);
            /* Update the link information in topology table */
            topology.addNewLink(new Link(link_id, link_cost));
            logBuffer.write("R"+router_id+" new topology Info:");
            logBuffer.newLine();
            logBuffer.write("R"+router_id+" -> "+"R"+topology.ownerID()+" link "+link_id+" cost "+link_cost);
            logBuffer.newLine();
            logBuffer.flush();
            logWriter.flush();
        }
        //topologyTable.add(topology);
        Topology_list.put(router_id, topology);
        sendHelloPacket(topology);
    }

	
	
	
	public static void main(String[] args) throws Exception {
        int id = -1;
        int port = -1;
        int r_port = -1;
        InetAddress host = null;
        switch(args.length){
        case 4:
        	id = Integer.parseInt(args[0]);
            host = InetAddress.getByName(args[1]);
            port = Integer.parseInt(args[2]);
            r_port = Integer.parseInt(args[3]);
        	break;
        default:
        	System.err.println("Number of arguments is wrong! Should input 4 arguments");
        	System.exit(-1);
        }

        router Router = new router(id,port,r_port,host);
        /* Create the .log file */
        String s = new String("router");
        s = s+Router.getID()+".log";
        Router.logWriter = new FileWriter(s);
//        Router.logBuffer = new BufferedWriter(r.logWriter);
//
//        Router.sendInitPacket();
//        Router.receiveCircuitDatabase();
//        Router.listener();
	}
}
