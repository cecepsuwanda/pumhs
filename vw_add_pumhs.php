<div class="form">   
   
    <form id="user-form" action="#" method="post">    
    <p class="note">Catatan : semua isian bertanda * perlu diisi.</p>
    
	<input type="hidden" id="ktp" value="<?php  echo $nomorKTP;?>">
	
	<h3>Fakultas dan Prodi</h3>
		
	<table>	
        <tbody>
        <tr>
            <td style="font-weight: bold">Fakultas dan Prodi</td>
            <td></td>
            <td></td>
            <td>
                <select name="Prodi" id="prodi" data-placeholder=" pilih program studi asal...">
<?php
					require_once "pumhs/dt/dt_prodi.class.inc";
					$dtprodi = new dt_prodi;
                    $data = $dtprodi->getdata('');                  
                    foreach ($data as $r){
						echo "<option ";
						if ($prod == $r['kd_prodi']) echo "selected='selected' ";
						echo "value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>
						";
					}
?>
                 </select>
            </td>
        </tr>

        <tr>
            <td style="font-weight: bold">Kelas</td>
            <td></td>
            <td></td>
            <td>
                <select name="kelas" id="kelas" data-placeholder=" pilih kelas...">
                    <option <?php if($kelas=="R") echo "selected" ?> value="R">Reguler</option>
					<option <?php if($kelas=="N") echo "selected" ?> value="N">Non Reguler</option>
                 </select>
            </td>
            <td></td>
        </tr>

	</tbody></table>	
	
	<h3>Identitas mahasiswa</h3>
		
	<table>	
        <tbody>
        <tr>
            <td><label for="nim">Nomor Pokok Mahasiswa </label></td>
            <td><input name="nim" id="nim" maxlength="9" type="text" value=<?php echo $nim?>></td>
            <td></td>
            <td></td>
            <td></td>
        </tr>		
		<tr>
            <td style="width: 133px;"><label for="namaMahasiswa" class="required">Nama Mahasiswa <span class="required">*</span></label></td>
            <td><input name="namaMahasiswa" id="namaMahasiswa" maxlength="30" type="text" value="<?php echo $Nama_mahasiswa ?>"></td>
            <td></td>

            <td><label for="statusMahasiswa" class="required">Status Mahasiswa <span class="required">*</span></label></td>
            <td>
                <select name="statusMahasiswa" id="statusMahasiswa" data-placeholder=" pilih status mahasiswa...">
                    <option <?php if($status=="A") echo "selected" ?> value="A">Aktif</option>
					<option <?php if($status=="C") echo "selected" ?> value="C">Cuti</option>
					<option <?php if($status=="L") echo "selected" ?> value="L">Lulus</option>
                </select>
            </td>
            <td></td>
		
        </tr>
        
        <tr>
            <td><label for="jenisKelamin" class="required">Jenis Kelamin <span class="required">*</span></label></td>
            <td>
                <select name="jenisKelamin" id="jenisKelamin">
                    <option <?php if($jenisKelamin == "P")echo "selected" ?> value="P">Perempuan</option>
                    <option <?php if($jenisKelamin == "L")echo "selected" ?> value="L">Laki-laki</option>
                </select>
            </td>
            <td></td>

            <td><label for="tempatLahir" class="required">Tempat Lahir <span class="required">*</span></label></td>
            <td><input name="tempatLahir" id="tempatLahir" maxlength="20" type="text" value=<?php echo $tempatLahir ?>></td>
            <td></td>
        </tr>

        <tr>
            <td><label for="alamat" class="required">Alamat <span class="required">*</span></label></td>
            <td><textarea name="alamat" id="alamat" maxlength="100" ><?php echo $alamat ?></textarea></td>
            <td></td>
            <td><label for="tanggalLahir" class="required">Tanggal Lahir <span class="required">*</span></label></td>
            <td><input name="tanggalLahir" id="tanggalLahir" type="text" onchange="checkKTP()" value ="<?php echo $tanggalLahir ?>"></td>
            <td></td>
        </tr>

        <tr>
            <td><label for="kota" class="required">Kabupaten / Kota <span class="required">*</span></label></td>
            <td>
                <select name="kota" id="kota" data-placeholder=" pilih kabupaten/kota...">
                    <option <?php if($kota=="") echo "selected" ?> value=""></option>
					<option <?php if($kota=="121451") echo "selected" ?> value="121451">Kota Bandung</option>
					<option <?php if($kota=="121452") echo "selected" ?> value="121452">Kabupaten Bandung</option>
					<option <?php if($kota=="121453") echo "selected" ?> value="121453">Kota Cimahi</option>
					<option <?php if($kota=="121454") echo "selected" ?> value="121454">Kabupaten Sumedang</option>
					<option <?php if($kota=="121455") echo "selected" ?> value="121455">Kabupaten Cianjur</option>
                </select>
            </td>
            <td></td>
            <td><label for="telepon" class="required">Telepon <span class="required">*</span></label></td>
            <td><input name="telepon" id="telepon" maxlength="20" type="text" onkeypress="return isNumberKey(event)" value=<?php echo $telepon ?>></td>
            <td></td>
        </tr>

        <tr>
            <td><label for="provinsi" class="required">Provinsi <span class="required">*</span></label></td>
            <td>
                <select name="provinsi" id="provinsi" data-placeholder=" pilih Provpinsi...">
                    <option <?php if($provinsi=="") echo "selected" ?> value=""></option>
					<option <?php if($provinsi=="121") echo "selected" ?> value="121">Jawa Barat</option>
					<option <?php if($provinsi=="122") echo "selected" ?>value="122">Jawa Tengah</option>
					<option <?php if($provinsi=="123") echo "selected" ?>value="123">Jawa Timur</option>
					<option <?php if($provinsi=="124") echo "selected" ?>value="124">DI Jogjakarta</option>
					<option <?php if($provinsi=="125") echo "selected" ?>value="125">DKI Jakarta</option>
                </select>
            </td>
            <td></td>
            <td><label for="hp" class="required">No. HP <span class="required">*</span></label></td>
            <td><input name="hp" id="hp" maxlength="20" type="text" onkeypress="return isNumberKey(event)" value=<?php echo $hp ?>></td>
        </tr>

        <tr>
            <td><label for="kodePos" >Kode Pos </label></td>
            <td><input name="kodePos" id="kodePos" maxlength="10" type="text" value=<?php echo $kodePos ?>></td>
            <td></td>

            <td><p></p>
			<label for="tanggalLulus" class="required" >Tanggal Lulus </label></td>
            <td><p class="note">Catatan : bagi mahasiswa yg sudah lulus...!</p>
			<input name="tanggalLulus" id="tanggalLulus" type="text" value="<?php echo $tanggalLulus ?>"></td>
            <td></td>
        </tr>

        <tr>
            <td><label for="tanggalMasuk" class="required">Tanggal Masuk <span class="required">*</span></label></td>
            <td><input name="tanggalMasuk" id="tanggalMasuk" type="text" onchange="thnMasuk()" value="<?php echo $tanggalMasuk ?>"></td>
            <td></td>

            <td><label for="ipkAkhir">IPK Akhir </label></td>
            <td><input name="ipkAkhir" id="ipkAkhir" maxlength="4" type="text" value=<?php echo $ipkAkhir ?>></td>
            <td></td>
        </tr>

        </tr>

        <tr>
            <td><label for="tahunMasuk" class="required">Tahun Masuk <span class="required">*</span></label></td>
            <!--- <td><input name="tahunMasuk" id="tahunMasuk" maxlength="4" type="text" value = "<?php //echo $tahunMasuk?>"></td> -->
            <td>  <select name="tahunMasuk" id="tahunMasuk" onchange="thnMasukX()">
			
                   <?php
                        $txt='';
						$tmp_date =date("Y");							
						for ($i=2006;$i<=$tmp_date;$i++){ 
						 if( $tahunMasuk==$i){
						    $txt.='<option selected value="'.$i.'">'.$i.'</option>';						     
						 }else
						    {
							 $txt.='<option value="'.$i.'">'.$i.'</option>';							
							}
                        }
						echo $txt;
    				?>   
					
				<!--<option <?php if( $tahunMasuk=="2009") echo "selected" ?> value="2009">2009</option>					
					<option <?php if( $tahunMasuk=="2010") echo "selected" ?> value="2010">2010</option>
					<option <?php if( $tahunMasuk=="2011") echo "selected" ?> value="2011">2011</option>
					<option <?php if( $tahunMasuk=="2012") echo "selected" ?> value="2012">2012</option>	
                    <option <?php if( $tahunMasuk=="2013") echo "selected" ?> value="2013">2013</option>
                    <option <?php if( $tahunMasuk=="2014") echo "selected" ?> value="2014">2014</option> -->

					
                 </select></td>
			<td></td>

            <td><label for="nomorSkYudisium">Nomor SK Yudisium </label></td>
            <td><input name="nomorSkYudisium" id="nomorSkYudisium" maxlength="30" type="text" value=<?php echo $nomorSkYudisium ?>></td>
            <td></td>
        </tr>

        <tr>
            <td><label for="batasStudi">Batas_Studi </label></td>
            <td><input name="batasStudi" id="batasStudi" maxlength="5" type="text" value=<?php echo $batasStudi ?>></td>
            <td></td>

            <td><label for="tanggalYudisium" class="required">Tanggal Yudisium </label></td>
            <td><input name="tanggalYudisium" id="tanggalYudisium" type="text" value="<?php echo $tanggalYudisium ?>"></td>
            <td></td>
        </tr>

        <tr>
            <td><label for="statusAwalMahasiswa" class="required">Status Awal Mahasiswa <span class="required">*</span></label></td>
            <td>
                <select name="statusAwalMahasiswa" id="statusAwalMahasiswa" data-placeholder=" pilih status Asal mahasiswa...">
                    <option selected="selected" value="B">Baru</option>
					<option value="P">Pindahan</option>
                </select>
            </td>
            <td></td>

            <td><label for="nomorSeriIjazah">Nomor Seri Ijazah </label></td>
            <td><input name="nomorSeriIjazah" id="nomorSeriIjazah" maxlength="40" type="text" value=<?php echo $nomorSeriIjazah ?>></td>
            <td></td>
        </tr>

	</tbody></table>

	<h3>Pendidikan Terakhir</h3>
    <p class="note">Catatan : bagi mahasiswa pindahan mohon perguruan tinggi asal, prodi asal dan SKS diakui harus diisi...!</p>

    <table>    
        <tbody>
		
        <tr>
            <td><label for="smaAsal" class="required">SMA Asal <span class="required">*</span></label></td>
            <td><input name="smaAsal" id="smaAsal" maxlength="40" type="text" value=<?php echo $smaAsal ?>></td>
            <td></td>
        </tr>

        <tr id="dn">
            <td style="font-weight: bold">Perguruan Tinggi Asal</td>
            <td>
                <select name="universitasAsal" id="universitasAsal" data-placeholder=" pilih perguruan tinggi asal...">
					<option selected="" value=""></option>
<?php
					require_once "pumhs/dt/dt_universitas.class.inc";
                    $dtuniv = new dt_universitas;
                    $data = $dtuniv->getdata('');     
					foreach($data as $r){
				      echo "<option ";
					  if ($universitasAsal==$r['Kode_Univ']) echo "selected ";
					  echo "value=".$r['Kode_Univ'].">".$r['Nama_Univ']." </option>
					  ";
				}
?>
                </select>
            </td>
        </tr>
        <tr>
            <td style="font-weight: bold">Fakultas dan Prodi asal</td>
            <td>
                <select name="prodiAsal" id="prodiAsal" data-placeholder=" pilih program studi asal...">
<?php
					$dtprodi = new dt_prodi;
                    $data = $dtprodi->getdata('');                  
					echo "<option selected='selected' value=''></option> ";
					foreach ($data as $r){
						echo "<option "; 
						if ($prodiAsal==$r['kd_prodi']) echo "selected ";
						echo "value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
					}
?>
                 </select>
            </td>
        </tr>
        <tr>
            <td><label for="sksDiakui">Jumlah SKS diakui </label></td>
            <td><input name="sksDiakui" id="sksDiakui" maxlength="3" type="text" value=<?php echo $sksDiakui ?>></td>
            <td></td>
        </tr>
	</tbody></table>

	<h3>Informasi Pekerjaan </h3>
    <p class="note">Catatan : mahasiswa yang berkerja harus diisi !</p>

    <table>    
        <tbody>

        <tr>
            <td style="font-weight: bold">Status Kerja</td>
            <td>
                <select name="kodePekerjaan" id="kodePekerjaan" data-placeholder=" pilih status pekerjaan...">
                    <option <?php if($kodePekerjaan=="J") echo "selected" ?> value="J">Belum bekerja</option>
					<option <?php if($kodePekerjaan=="G") echo "selected" ?> value="G">Pegawai Swasta</option>					
					<option <?php if($kodePekerjaan=="I") echo "selected" ?> value="I">Wiraswasta</option>
					<option <?php if($kodePekerjaan=="H") echo "selected" ?> value="H">LSM</option>
					<option <?php if($kodePekerjaan=="E") echo "selected" ?> value="E">PNS Lembaga Pemerintahan</option>
					<option <?php if($kodePekerjaan=="K") echo "selected" ?> value="K">Guru honor</option>
					<option <?php if($kodePekerjaan=="D") echo "selected" ?> value="D">Dosen PTS</option>
					<option <?php if($kodePekerjaan=="C") echo "selected" ?> value="C">Dosen DPK PTS</option>
					<option <?php if($kodePekerjaan=="B") echo "selected" ?> value="B">Dosen kontrak PTN/ BHMN</option>
					<option <?php if($kodePekerjaan=="A") echo "selected" ?> value="A">Dosen PNS PTN/ BHMN</option>
					<option <?php if($kodePekerjaan=="F") echo "selected" ?> value="F">TNI/POLRI</option>
                 </select>
            </td>
        </tr>

        <tr>
            <td><label for="namaTempatPekerjaan">Nama Tempat Bekerja </label></td>
            <td><textarea name="namaTempatPekerjaan" id="namaTempatPekerjaan" maxlength="40" ><?php echo $namaTempatPekerjaan ?></textarea></td>
            <td></td>
        </tr>

		</tbody>
	</table>
	
    <div class="row buttons">
        <input name="yt0" value="Update Data" type="button" onclick="cekform()">   
        <input name="yt1" value="Log Out" type="button" onclick="logout()">    </div>
    </form>
   </div>