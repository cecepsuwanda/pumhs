if(($row['Tgl_Log']==null) and ($row['optcid']==null) and ($row['optuid']==null) )
                $txt = $txt."<li>Silahkan login untuk melengkapi data !!!</li>";}				
				else{ 
					  
				//	    if(($row['NIM']=="")){
				//		 if ($row['Tahun_masuk']<$tmp_date)  
				//		   $txt = $txt."<li>NIM mohon diisi</li>";
				//		   $cek_nim=1;
				//		  else 
				//		    $cek_nim=1;
				//		 
				//	 else
				//	  					
				//		$cek_nim=0;
				//		$subject =$row['NIM'];
				//		$pattern = "/[A-Ga-g]1[A-Ga-g][0-9]{6/";				
				//		if(($row['NIM']!="") && (preg_match($pattern,$subject)==0)){
				//		  $txt = $txt."<li>NIM salah tulis !!!</li>";
				//		  $cek_nim=1;
				//		else
				//		  
				//		  if(strcmp($row['kd_fakultas'],'FAPERTA')==0){
				//		     $pattern = "/[Aa]1[A-Ca-c][0-9]{6/";
				//			 if((preg_match($pattern,$subject)==0)){
				//		        $txt = $txt."<li>Bukan NIM Fakultas Pertanian !!!</li>";
				//				$cek_nim=1;
				//		       
				//		 else
				//		    if(strcmp($row['kd_fakultas'],'FE')==0){
				//		       $pattern = "/[Ee]1[Aa][0-9]{6/";
				//			   if((preg_match($pattern,$subject)==0)){
				//		          $txt = $txt."<li>Bukan NIM Fakultas Ekonomi !!!</li>";
				//				  $cek_nim=1;
				//		      
				//		   else
                 //            if(strcmp($row['kd_fakultas'],'FISIP')==0){
				//		          $pattern = "/[Dd]1[Aa][0-9]{6/";
				//			      if((preg_match($pattern,$subject)==0)){
				//		             $txt = $txt."<li>Bukan NIM FISIP !!!</li>";
				//					 $cek_nim=1;
				//		         
				//		       else
				//	           if(strcmp($row['kd_fakultas'],'FIKES')==0){
				//		             $pattern = "/[Gg]1[Aa][0-9]{6/";
				//			         if((preg_match($pattern,$subject)==0)){
				//		                $txt = $txt."<li>Bukan NIM Fakultas Kesehatan !!!</li>";
				//						$cek_nim=1;
				//		            
				//		          else
				//	              if(strcmp($row['kd_fakultas'],'FMIPA')==0){
				//		                $pattern = "/[Ff]1[Aa][0-9]{6/";
				//			            if((preg_match($pattern,$subject)==0)){
				//		                   $txt = $txt."<li>Bukan NIM Fakultas MIPA !!!</li>";
				//						   $cek_nim=1;
				//		               
				//		             else
				//	                  if(strcmp($row['kd_fakultas'],'FKIP')==0){
				//		                    $pattern = "/[Bb]1[A-Da-d][0-9]{6/";
				//			                if((preg_match($pattern,$subject)==0)){
				//		                        $txt = $txt."<li>Bukan NIM FKIP !!!</li>";
				//								$cek_nim=1;
				//		                   else
				//							
				//							  if(strcmp($row['kd_prodi'],'GEO')==0){
				//		                             $pattern = "/[Bb]1[Aa][0-9]{6/";
				//			                         if((preg_match($pattern,$subject)==0)){
				//		                                $txt = $txt."<li>Bukan NIM Prodi Geografi !!!</li>";
				//								        $cek_nim=1;
				//		                                 
				//							     
				//								  
				//								  if(strcmp($row['kd_prodi'],'IND')==0){
				//		                             $pattern = "/[Bb]1[Cc][0-9]{6/";
				//			                         if((preg_match($pattern,$subject)==0)){
				//		                                $txt = $txt."<li>Bukan NIM Prodi Bahasa Indonesia !!!</li>";
				//								        $cek_nim=1;
				//		                                 
				//							     
				//							      
				//								  if(strcmp($row['kd_prodi'],'ING')==0){
				//		                             $pattern = "/[Bb]1[Bb][0-9]{6/";
				//			                         if((preg_match($pattern,$subject)==0)){
				//		                                $txt = $txt."<li>Bukan NIM Prodi Bahasa Inggris !!!</li>";
				//								        $cek_nim=1;
				//		                                 
				//							     
				//								  
				//								  if(strcmp($row['kd_prodi'],'IPS')==0){
				//		                             $pattern = "/[Bb]1[Dd][0-9]{6/";
				//			                         if((preg_match($pattern,$subject)==0)){
				//		                                $txt = $txt."<li>Bukan NIM Prodi IPS !!!</li>";
				//								        $cek_nim=1;
				//		                                 
				//							     
				//								  
				//							
				//							
					                  //}else
									  //if(strcmp($row['kd_fakultas'],'FTI')==0){
						                       //$pattern = "/[Cc]1[A-Ba-b][0-9]{6/";
							                   //if((preg_match($pattern,$subject)==0)){
						                        //  $txt = $txt."<li>Bukan NIM Fakultas Teknologi Informasi !!!</li>";
												//  $cek_nim=1;
						                       //}else
											   
											      //if(strcmp($row['kd_prodi'],'IF')==0){
						                          //   $pattern = "/[Cc]1[Aa][0-9]{6/";
							                      //   if((preg_match($pattern,$subject)==0)){
						                          //      $txt = $txt."<li>Bukan NIM Prodi Teknik Informatika !!!</li>";
												  //      $cek_nim=1;
						                          //   }     
											     // }
												  
												  //if(strcmp($row['kd_prodi'],'SI')==0){
						                            // $pattern = "/[Cc]1[Bb][0-9]{6}/";
							                        // if((preg_match($pattern,$subject)==0)){
						                             //   $txt = $txt."<li>Bukan NIM Prodi Sistem Informasi !!!</li>";
												      //  $cek_nim=1;
						                             //}     
											      //}
											   
											   //}
						                   // }
						  
						                 //} 
						  
					//	              }
					//	  
					//	          }
					//	  
					//	        }					  
					 // 
					//	    }
					//	  
					//	  }
					//	
					//	}
					//	
				  //} 
				  }
					  

					  
					  if($row['Alamat']==""){
						
						$txt = $txt."<li>Alamat mohon dilengkapi !!!</li>";
					  }				   
					   
					   if($row['Tahun_masuk']=="0000"){						
						$txt = $txt."<li>Tahun Masuk mohon diisi !!!</li>";
					  }else{
						 
						 if(($row['Tahun_masuk'])>$tmp_date){
							$txt = $txt."<li>Tahun Masuk salah !!!</li>";
						  }else{
							
							 $parts = explode("-",$row['Tanggal_masuk']);   
							 if( ($row['Tahun_masuk']!="0000") && ($row['Tanggal_masuk'] != null) && ($parts[0]!=$row['Tahun_masuk'])){
								 
                                 if($row['Tanggal_masuk'] == "0000-00-00"){
                                    $tmp_tgl=$row['Tahun_masuk']."-09-23";	
                                 }									
								 else {
  								    $tmp_tgl=$row['Tahun_masuk'].'-'.$parts[1].'-'.$parts[2]; 
									
								  }
								  
								  if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){
								     $this->dt_mhs->update_tgl_msk($row['NO_KTP'],$tmp_tgl);
								  }
								  //$txt = $txt."<li>Tahun  Masuk dan Tanggal Masuk tak sesuai</li>";
							 }
                             
                             if($cek_nim==0){
							    if( ($row['Tahun_masuk']!="0000")){		
								  $tmp1=substr($row['NIM'],4,1);
								  $tmp2=substr($row['Tahun_masuk'],3,1);
								 if(strcmp($tmp1,$tmp2)!=0) {
								   $txt = $txt."<li>Tahun  Masuk dan NIM tak sesuai</li>";
								 } 
							 }
							 
							 }							 
							 
						  }
					  
					  }
					   
					   
						if(strlen($row['NO_KTP'])==16) 
						{				   				   
							$subject =$row['NO_KTP'];
							$pattern = "/[1 3][1-8][0-2 7][0-9][0-4][0-9][0-7][0-9][0-1][0-9][0-1 5-9][0-9]{4}/";				
				  
						  if(preg_match($pattern,$subject)==0){
						     $pattern = "/12345[0-6][0-9]{8}/";							 
							 if(preg_match($pattern,$subject)==0){
							   $txt = $txt."<li>PUMHS tidak mengenali format no KTP anda, silakan hubungi operator untuk mengisi form PUMHS Off line !!! </li>";
							 }
						  }
						  
								if($row['Tanggal_lahir']=="0000-00-00"){
									$txt = $txt."<li>Tgl lahir harap diisi !!!</li>";
								}  
								else{ 
								  //$tmp = date('dmy',strtotime($row['Tanggal_lahir']));
								  //if($row['Jenis_kelamin']=='P'){
									 $parts = explode("-",$row['Tanggal_lahir']);
									 //$tmp = intval($parts[2])+40;
									 $tmp = intval($parts[2]) % 10;
									 $tmp = $tmp.$parts[1].(substr($parts[0],-2));
								  //}					  
								  
								  $tmp1 = substr($row['NO_KTP'],7,5);
								  
								   if($tmp!=$tmp1){
									
									$txt = $txt."<li>Tgl lahir tidak sesuai KTP, silakan login untuk memperbaiki !!!</li>";
								  }
								} 
						  
					  }
								   
					   if($txt=="")
						{
						$txt = "<li>Data Lengkap</li>";
						
                          if($row['verifikasi']==1){ 
						      if($this->dt_mhs->is_nim_double($row['NIM']))
						      {
						        $txt .= "<li>NIM Double !!!</li>";
						      }
						      if($this->dt_mhs->is_nm_double(addslashes($row['Nama_mahasiswa'])))
							  {
								$txt .= "<li>Nama Double !!!</li>";
							  }
						   }
						
						 if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){
						    $this->dt_mhs->update_validasi($row['NO_KTP'],1);
                           	if( $row['verifikasi']==0 and $row['kd_fakultas']=='FTI' and $row['kd_fakultas']=='FE' and $row['kd_fakultas']=='FMIPA'){
							   if($this->dt_mhs_epsbed->is_exist($row['NIM'],addslashes($row['Nama_mahasiswa']))){
							   $optudate= date("Y-m-d H:i:s");
							   $this->dt_mhs->update_verifikasi($row['NO_KTP'],1,$optudate,"System");							
							  }	
							} 				  
						 }  
						}else{
						  
						  if(($txt=="<li>NIM mohon diisi</li>") && (($row['NIM']=="") &&($row['Tahun_masuk']==2013)))
                          {
						      if($row['verifikasi']==1){ 
							      if($this->dt_mhs->is_nm_double(addslashes($row['Nama_mahasiswa'])))
								  {
									$txt .= "<li>Nama Double !!!</li>";
								  }	
							  }						  
							if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){  
						      $this->dt_mhs->update_validasi($row['NO_KTP'],1);
                              if($row['verifikasi']==0 and $row['kd_fakultas']=='FTI' and $row['kd_fakultas']=='FE' and $row['kd_fakultas']=='FMIPA' ) {
							   if($this->dt_mhs_epsbed->is_exist($row['NIM'],addslashes($row['Nama_mahasiswa']))){
								   $optudate= date("Y-m-d H:i:s");
								   $this->dt_mhs->update_verifikasi($row['NO_KTP'],1,$optudate,"System");							
							   }
                              }							   
						    }
						  }else{						  
						    
							if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){ 						       
							   $this->dt_mhs->update_validasi($row['NO_KTP'],0);
						    }
						   }
						
						}
					}