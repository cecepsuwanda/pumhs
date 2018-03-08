<?php
require_once 'default_table.class.inc';
class tb_stat_mhs extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'stat_mhs';
        
		$this->fieldlist       = array('thnsmsstat_mhs','noktp_mhs','statstat_mhs','optuid','optudate','kd_prodi','kd_fak');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['thnsmsstat_mhs'] = array('pkey' => 'y');
		$this->fieldlist['noktp_mhs'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>

