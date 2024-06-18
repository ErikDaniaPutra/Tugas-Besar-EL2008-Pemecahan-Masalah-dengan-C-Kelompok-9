import tkinter as tk
import re
from tkinter import simpledialog, messagebox, ttk
from subprocess import Popen, PIPE, STDOUT

# Dictionary untuk memetakan pilihan diagnosa ke nilai integer
diagnosa_mapping = {
    "Masuk Angin": 1,
    "Dehidrasi": 2,
    "Keseleo": 3,
    "Pusing": 4
}

# Dictionary untuk memetakan pilihan tindakan ke nilai integer
tindakan_mapping = {
    "Pemeriksaan (Rp125000)": 1,
    "Vaksinasi (Rp100000)": 2,
    "Cek gula darah (Rp25000)": 3,
    "Pemasangan infus (Rp125000)": 4,
    "Pengobatan (Rp150000)": 5
}

def run_process(stdin: str) -> str:
    process = Popen(['./main.exe'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    stdout, stderr = process.communicate(input=stdin.encode())

    if stderr:
        return None

    return stdout.decode()

def main():
    # Function to handle button clicks
    def handle_click(feature):
        if feature == "Ubah/Tambah Data Pasien":
            show_data_pasien_window()
        
        elif feature == "Riwayat Pasien":
            show_riwayat_pasien_window()
        
        elif feature == "Informasi Pasien":
            # Prompt user for ID Pasien
            id_pasien = simpledialog.askstring("Input ID Pasien", "Masukkan ID Pasien:")
            if id_pasien:
                # Execute process "9 {ID Pasien} 0"
                output = run_process(f"9 {id_pasien}\n 0")
                if output:
                    if "Pasien tidak ditemukan" in output:
                        show_error_message("Pasien tidak ditemukan.", "Error")
                    else:
                        # Regex to capture relevant output
                        result = re.search(r'Masukkan ID Pasien: (.*?)Sistem Pencatatan Pasien Klinik X', output, re.DOTALL)
                        if result:
                            info_text = result.group(1).strip()
                            show_custom_message(info_text, "Informasi Pasien")
                        else:
                            show_custom_message("No matching text found.", "Informasi Pasien")
                else:
                    show_error_message("An error occurred while running the process.", "Error")
        
        elif feature == "Laporan Pendapatan":
            output = run_process("10 0")
            if output:
                amount_match = re.search(r'Jumlah data riwayat pasien: (\d+)', output)
                report_match = re.search(r'Laporan Pendapatan Bulanan:(.*)Sistem Pencatatan Pasien Klinik X', output, re.DOTALL)
                if amount_match and report_match:
                    amount = amount_match.group(1)
                    report = report_match.group(1).strip()
                    full_report = f"Jumlah data riwayat pasien: {amount}\n\n{report}"
                    show_custom_message(full_report, "Laporan Pendapatan")
                else:
                    show_custom_message("No matching text found.", "Laporan Pendapatan")
            else:
                show_custom_message("An error occurred while running the process.", "Laporan Pendapatan")

        elif feature == "Laporan Pasien":
            output = run_process("11 0")
            if output:
                amount_match = re.search(r'Jumlah data riwayat pasien: (\d+)', output)
                report_match = re.search(r'Laporan Jumlah Pasien Bulanan:(.*)Sistem Pencatatan Pasien Klinik X', output, re.DOTALL)
                if amount_match and report_match:
                    amount = amount_match.group(1)
                    report = report_match.group(1).strip()
                    full_report = f"Jumlah data riwayat pasien: {amount}\n\n{report}"
                    show_custom_message(full_report, "Laporan Pasien")
                else:
                    show_custom_message("No matching text found.", "Laporan Pasien")
            else:
                show_custom_message("An error occurred while running the process.", "Laporan Pasien")

        elif feature == "Daftar Pasien yang Perlu Kontrol":
            output = run_process("12 0")
            if output:
                result = re.search(r'Pasien yang Perlu Kembali Kontrol:(.*)Sistem Pencatatan Pasien Klinik X', output, re.DOTALL)
                if result:
                    show_custom_message(result.group(1).strip(), "Daftar Pasien yang Perlu Kontrol")
                else:
                    show_custom_message("No matching text found.", "Daftar Pasien yang Perlu Kontrol")
            else:
                show_custom_message("An error occurred while running the process.", "Daftar Pasien yang Perlu Kontrol")
        

        else:
            messagebox.showinfo("Fitur", f"Anda mengklik {feature}")

    # Function to exit the application
    def exit_program():
        root.destroy()

    # Function to show custom message with a scrollbar
    def show_custom_message(message, title):
        custom_msg = tk.Toplevel(root)
        custom_msg.title(title)
        custom_msg.geometry("800x600")

        tk.Label(custom_msg, text=title, font=("Arial", 14)).pack(pady=10)

        text_frame = tk.Frame(custom_msg)
        text_frame.pack(fill=tk.BOTH, expand=True)

        text_box = tk.Text(text_frame, wrap="word")
        text_box.insert(tk.END, message)
        text_box.config(state=tk.DISABLED)

        scroll_bar = tk.Scrollbar(text_frame, command=text_box.yview)
        text_box.config(yscrollcommand=scroll_bar.set)

        text_box.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scroll_bar.pack(side=tk.RIGHT, fill=tk.Y)

        tk.Button(custom_msg, text="Close", command=custom_msg.destroy).pack(pady=10)

    # Function to show small message
    def show_custom_message_large(message, title):
        custom_msg = tk.Toplevel(root)
        custom_msg.title(title)
        custom_msg.geometry("1100x180")

        tk.Label(custom_msg, text=title, font=("Arial", 14)).pack(pady=10)

        text_frame = tk.Frame(custom_msg)
        text_frame.pack(fill=tk.BOTH, expand=True)

        text_box = tk.Text(text_frame, wrap="word")
        text_box.insert(tk.END, message)
        text_box.config(state=tk.DISABLED)

        scroll_bar = tk.Scrollbar(text_frame, command=text_box.yview)
        text_box.config(yscrollcommand=scroll_bar.set)

        text_box.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scroll_bar.pack(side=tk.RIGHT, fill=tk.Y)

        tk.Button(custom_msg, text="Close", command=custom_msg.destroy).pack(pady=10)

    def show_custom_message_small(message, title):
        custom_msg = tk.Toplevel(root)
        custom_msg.title(title)
        custom_msg.geometry("400x300")

        tk.Label(custom_msg, text=title, font=("Arial", 14)).pack(pady=10)

        text_frame = tk.Frame(custom_msg)
        text_frame.pack(fill=tk.BOTH, expand=True)

        text_box = tk.Text(text_frame, wrap="word")
        text_box.insert(tk.END, message)
        text_box.config(state=tk.DISABLED)

        scroll_bar = tk.Scrollbar(text_frame, command=text_box.yview)
        text_box.config(yscrollcommand=scroll_bar.set)

        text_box.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scroll_bar.pack(side=tk.RIGHT, fill=tk.Y)

        tk.Button(custom_msg, text="Close", command=custom_msg.destroy).pack(pady=10)

    # Function to show error message
    def show_error_message(message, title):
        messagebox.showerror(title, message)

    # Function to show data pasien window
    def show_data_pasien_window():
        data_pasien_window = tk.Toplevel(root)
        data_pasien_window.title("Data Pasien")
        data_pasien_window.geometry("300x320")

        tk.Label(data_pasien_window, text="Pilih operasi yang diinginkan:", font=("Arial", 14)).pack(pady=10)

        tk.Button(data_pasien_window, text="Tambah data pasien", command=tambah_data_pasien).pack(pady=5)
        tk.Button(data_pasien_window, text="Ubah data pasien", command=ubah_data_pasien).pack(pady=5)
        tk.Button(data_pasien_window, text="Hapus data pasien", command=hapus_data_pasien).pack(pady=5)
        tk.Button(data_pasien_window, text="Cari data pasien", command=cari_data_pasien).pack(pady=5)
        tk.Button(data_pasien_window, text="Back", command=data_pasien_window.destroy).pack(pady=5)
    
    def show_riwayat_pasien_window():
        riwayat_pasien_window = tk.Toplevel(root)
        riwayat_pasien_window.title("Riwayat Pasien")
        riwayat_pasien_window.geometry("400x300")

        tk.Label(riwayat_pasien_window, text="Pilih operasi yang diinginkan:", font=("Arial", 14)).pack(pady=10)

        tk.Button(riwayat_pasien_window, text="Tambah riwayat pasien", command=tambah_riwayat_pasien).pack(pady=5)
        tk.Button(riwayat_pasien_window, text="Ubah riwayat pasien", command=ubah_riwayat_pasien).pack(pady=5)
        tk.Button(riwayat_pasien_window, text="Hapus riwayat pasien", command=hapus_riwayat_pasien).pack(pady=5)
        tk.Button(riwayat_pasien_window, text="Cari riwayat pasien", command=cari_riwayat_pasien).pack(pady=5)
        tk.Button(riwayat_pasien_window, text="Back", command=riwayat_pasien_window.destroy).pack(pady=5)

    # Functions for data pasien operations (dummy functions)
    def tambah_data_pasien():
        # Create a new window for input
        input_window = tk.Toplevel(root)
        input_window.title("Tambah Data Pasien")
        input_window.geometry("500x200")

        labels = ["Nama Pasien", "Alamat Pasien", "Kota", "Tempat Lahir", "Tanggal Lahir", "Umur", "BPJS", "ID Pasien"]
        entries = []

        for i, label in enumerate(labels):
            tk.Label(input_window, text=label).grid(row=i//2, column=(i%2)*2, padx=7, pady=7, sticky="e")
            entry = tk.Entry(input_window)
            entry.grid(row=i//2, column=(i%2)*2 + 1, padx=7, pady=7)
            entries.append(entry)

        def submit():
            # Collect all inputs
            nama_pasien, alamat_pasien, kota, tempat_lahir, tanggal_lahir, umur, bpjs, id_pasien = (entry.get() for entry in entries)

            # Validate that umur is an integer
            try:
                umur = int(umur)
            except ValueError:
                messagebox.showerror("Error", "Umur harus berupa angka.")
                return

            if all([nama_pasien, alamat_pasien, kota, tempat_lahir, tanggal_lahir, umur]):
                # Construct the process input
                process_input = f"1 {nama_pasien}\n{alamat_pasien}\n{kota}\n{tempat_lahir}\n{tanggal_lahir}\n{umur}\n{bpjs}\n{id_pasien}\n 0"
                # Run the process and print the result
                result = run_process(process_input)
                print(result)
                messagebox.showinfo("Data Pasien", "Pasien berhasil ditambahkan.")
                input_window.destroy()
            else:
                messagebox.showerror("Error", "Semua bidang harus diisi.")

        tk.Button(input_window, text="Back", command=input_window.destroy).grid(row=4, column=0, columnspan= 4, pady=20)
        tk.Button(input_window, text="Submit", command=submit).grid(row=4, column=2, columnspan= 1, pady=20)
        
    def ubah_data_pasien():
        nama_pasien = simpledialog.askstring("Input Nama Pasien", "Masukkan Nama:")
        if nama_pasien:
            output = run_process(f"2\n{nama_pasien}\n{nama_pasien}\n12\n12\n12\n12\n12\n0\n12\n12\n0")

            if output:
                if "Data tidak ditemukan." in output:
                    show_error_message("Pasien tidak ditemukan.", "Error")
                else:
                    # Create a new window for input
                    update_window = tk.Toplevel(root)
                    update_window.title("Ubah Data Pasien")
                    update_window.geometry("500x200")

                    labels = ["Nama Pasien", "Alamat Pasien", "Kota", "Tempat Lahir", "Tanggal Lahir", "Umur", "BPJS", "ID Pasien"]
                    entries = []

                    for i, label in enumerate(labels):
                        tk.Label(update_window, text=label).grid(row=i//2, column=(i%2)*2, padx=7, pady=7, sticky="e")
                        entry = tk.Entry(update_window)
                        entry.grid(row=i//2, column=(i%2)*2 + 1, padx=7, pady=7)
                        entries.append(entry)

                    def submit():
                        # Collect all inputs
                        nama_pasien_baru, alamat_pasien, kota, tempat_lahir, tanggal_lahir, umur, bpjs, id_pasien = (entry.get() for entry in entries)

                        # Validate that umur is an integer
                        try:
                            umur = int(umur)
                        except ValueError:
                            messagebox.showerror("Error", "Umur harus berupa angka.")
                            return

                        if all([nama_pasien_baru, alamat_pasien, kota, tempat_lahir, tanggal_lahir, umur, bpjs, id_pasien]):
                            # Construct the process input
                            process_input = f"2\n{nama_pasien}\n{nama_pasien_baru}\n{alamat_pasien}\n{kota}\n{tempat_lahir}\n{tanggal_lahir}\n{umur}\n{bpjs}\n{id_pasien}\n0"
                            # Run the process and print the result
                            result = run_process(process_input)
                            messagebox.showinfo("Data Pasien", "Pasien berhasil diperbarui.")
                            update_window.destroy()
                        else:
                            messagebox.showerror("Error", "Semua bidang harus diisi.")

                    tk.Button(update_window, text="Back", command=update_window.destroy).grid(row=4, column=0, columnspan= 4, pady=20)
                    tk.Button(update_window, text="Submit", command=submit).grid(row=4, column=2, columnspan= 1, pady=20)
            else:
                show_error_message("An error occurred while running the process.", "Error")  

    def hapus_data_pasien():
        nama_pasien = simpledialog.askstring("Input Nama Pasien", "Masukkan Nama:")
        if nama_pasien:
                # Execute process "9 {ID Pasien} 0"
                output = run_process(f"3 {nama_pasien}\n 0")
                if output:
                    if "Data tidak ditemukan." in output:
                        show_error_message("Pasien tidak ditemukan.", "Error")
                    else:
                        # Regex to capture relevant output
                        messagebox.showinfo("Data Pasien", "Data berhasil dihapus.")
                else:
                    show_error_message("An error occurred while running the process.", "Error")

    def cari_data_pasien():
        nama_pasien = simpledialog.askstring("Input Nama Pasien", "Masukkan Nama:")
        if nama_pasien:
                # Execute process "9 {ID Pasien} 0"
                output = run_process(f"4 {nama_pasien}\n 0")
                if output:
                    if "Data tidak ditemukan." in output:
                        show_error_message("Pasien tidak ditemukan.", "Error")
                    else:
                        # Regex to capture relevant output
                        messagebox.showinfo("Data Pasien", "Data ditemukan.")
                        result = re.search(r'Data ditemukan:(.*?)Sistem Pencatatan Pasien Klinik X', output, re.DOTALL)
                        if result:
                            info_text = result.group(1).strip()
                            show_custom_message_small(info_text, "Informasi Pasien")
                        else:
                            show_custom_message_small("No matching text found.", "Informasi Pasien")
                else:
                    show_error_message("An error occurred while running the process.", "Error")

    # Functions for riwayat pasien operations (dummy functions)
    def tambah_riwayat_pasien():
        tambah_window = tk.Toplevel(root)
        tambah_window.title("Tambah Riwayat Pasien")
        tambah_window.geometry("400x400")

        tk.Label(tambah_window, text="Tambah Riwayat Pasien", font=("Arial", 14)).pack(pady=10)

        tk.Label(tambah_window, text="Tanggal:").pack()
        tanggal_entry = tk.Entry(tambah_window)
        tanggal_entry.pack()

        tk.Label(tambah_window, text="ID Pasien:").pack()
        id_pasien_entry = tk.Entry(tambah_window)
        id_pasien_entry.pack()

        # Combobox for Diagnosa
        tk.Label(tambah_window, text="Pilih Diagnosis:").pack()
        diagnosa_combobox = ttk.Combobox(tambah_window, values=list(diagnosa_mapping.keys()))
        diagnosa_combobox.pack()

        # Combobox for Tindakan
        tk.Label(tambah_window, text="Pilih Tindakan:").pack()
        tindakan_combobox = ttk.Combobox(tambah_window, values=list(tindakan_mapping.keys()))
        tindakan_combobox.pack()

        tk.Label(tambah_window, text="Kontrol:").pack()
        kontrol_entry = tk.Entry(tambah_window)
        kontrol_entry.pack()

        def submit_riwayat():
            tanggal = tanggal_entry.get()
            id_pasien = id_pasien_entry.get()
            diagnosa = diagnosa_combobox.get()  # Get selected diagnosa
            tindakan = tindakan_combobox.get()  # Get selected tindakan
            kontrol = kontrol_entry.get()

            if tanggal and id_pasien and diagnosa and tindakan and kontrol:
                # Get integer values from mappings
                diagnosa_value = diagnosa_mapping.get(diagnosa)
                tindakan_value = tindakan_mapping.get(tindakan)

                if diagnosa_value is None or tindakan_value is None:
                    show_error_message("Invalid selection.", "Input Error")
                    return
                
                # Run process with the collected data
                input_data = f"5 {tanggal}\n {id_pasien}\n {diagnosa_value} {tindakan_value} {kontrol}\n 0"
                output = run_process(input_data)
                if output:
                    messagebox.showinfo("Success", "Data riwayat pasien berhasil ditambah.")
                else:
                    show_error_message("An error occurred while adding the patient history.", "Error")
                tambah_window.destroy()
            else:
                show_error_message("Please fill in all fields.", "Input Error")

        tk.Button(tambah_window, text="Submit", command=submit_riwayat).pack(pady=10)
        tk.Button(tambah_window, text="Back", command=tambah_window.destroy).pack(pady=10)

    def ubah_riwayat_pasien():
        id_pasien = simpledialog.askstring("Input ID Pasien", "Masukkan ID Pasien:")
        if id_pasien:
            output = run_process(f'6 {id_pasien}\n 0 0')
            if output:
                if "Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan." in output:
                    show_error_message("Riwayat pasien tidak ditemukan.", "Error")
                else:
                    # Extract record entries using regex
                    records = re.findall(r'(Riwayat pasien \d+: Tanggal: [^,]+, Diagnosis: [^,]+, Tindakan: [^,]+, Kontrol: [^,]+, Biaya \(Rp\): \d+)', output)
                    if records:
                        record_numbers = [re.search(r'Riwayat pasien (\d+):', record).group(1) for record in records]
                        record_list = "\n".join(records)
                        
                        record_number = simpledialog.askstring("Ubah Riwayat Pasien", 
                            record_list + "\n\nMasukkan nomor urut rekam medis pasien untuk diubah:")
                        
                        if str(record_number) in record_numbers:
                            tanggal = ""
                            diagnosis = ""
                            tindakan = ""
                            kontrol = ""

                            ubah_window = tk.Toplevel(root)
                            ubah_window.title("Ubah Riwayat Pasien")
                            ubah_window.geometry("400x400")

                            tk.Label(ubah_window, text="Ubah Riwayat Pasien", font=("Arial", 14)).pack(pady=10)

                            tk.Label(ubah_window, text="Tanggal:").pack()
                            tanggal_entry = tk.Entry(ubah_window)
                            tanggal_entry.pack()
                            tanggal_entry.insert(tk.END, tanggal)

                            tk.Label(ubah_window, text="ID Pasien:").pack()
                            id_pasien_entry = tk.Entry(ubah_window, state=tk.DISABLED)
                            id_pasien_entry.pack()
                            id_pasien_entry.insert(tk.END, id_pasien)

                            # Combobox for Diagnosa
                            tk.Label(ubah_window, text="Pilih Diagnosis:").pack()
                            diagnosa_combobox = ttk.Combobox(ubah_window, values=list(diagnosa_mapping.keys()))
                            diagnosa_combobox.pack()
                            diagnosa_combobox.set(diagnosis)

                            # Combobox for Tindakan
                            tk.Label(ubah_window, text="Pilih Tindakan:").pack()
                            tindakan_combobox = ttk.Combobox(ubah_window, values=list(tindakan_mapping.keys()))
                            tindakan_combobox.pack()
                            tindakan_combobox.set(tindakan)

                            tk.Label(ubah_window, text="Kontrol:").pack()
                            kontrol_entry = tk.Entry(ubah_window)
                            kontrol_entry.pack()
                            kontrol_entry.insert(tk.END, kontrol)

                            def submit_perubahan():
                        
                                tanggal_baru = tanggal_entry.get()
                                diagnosa_baru = diagnosa_combobox.get()  # Get selected diagnosa
                                tindakan_baru = tindakan_combobox.get()  # Get selected tindakan
                                kontrol_baru = kontrol_entry.get()

                                if tanggal_baru and diagnosa_baru and tindakan_baru and kontrol_baru:
                                    # Get integer values from mappings
                                    diagnosa_value = diagnosa_mapping.get(diagnosa_baru)
                                    tindakan_value = tindakan_mapping.get(tindakan_baru)

                                    if diagnosa_value is None or tindakan_value is None:
                                        show_error_message("Invalid selection.", "Input Error")
                                        return
                                    
                                    # Run process with the collected data
                                    input_data = f"6 {id_pasien}\n {record_number} {tanggal_baru}\n {diagnosa_value} {tindakan_value} {kontrol_baru}\n 0"
                                    output = run_process(input_data)
                                    
                                    if output:
                                        messagebox.showinfo("Success", "Data riwayat pasien berhasil dihapus.")
                                    else:
                                        show_error_message("An error occurred while updating the patient history.", "Error")
                                    ubah_window.destroy()
                                else:
                                    show_error_message("Please fill in all fields.", "Input Error")

                            tk.Button(ubah_window, text="Submit", command=submit_perubahan).pack(pady=10)
                            tk.Button(ubah_window, text="Cancel", command=ubah_window.destroy).pack(pady=10)
                        else:
                            show_error_message("Nomor urut rekam medis tidak valid.", "Error")
                    else:
                        show_error_message("Tidak ada riwayat yang ditemukan untuk ID pasien ini.", "Error")
            else:
                show_error_message("Terjadi kesalahan saat menjalankan proses.", "Error")
        else:
            show_error_message("ID pasien tidak boleh kosong.", "Error")

    def hapus_riwayat_pasien():
        id_pasien = simpledialog.askstring("Input ID Pasien", "Masukkan ID Pasien:")
        if id_pasien:
            output = run_process(f'7 {id_pasien}\n 0 0')
            if output:
                if "Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan." in output:
                    show_error_message("Riwayat pasien tidak ditemukan.", "Error")
                else:
                    # Extract record entries using regex
                    records = re.findall(r'(Rekam medis \d+: Tanggal: [^,]+, Diagnosis: [^,]+, Tindakan: [^,]+, Kontrol: [^,]+, Biaya \(Rp\): \d+)', output)
                    if records:
                        record_numbers = [re.search(r'Rekam medis (\d+):', record).group(1) for record in records]
                        record_list = "\n".join(records)
                        
                        record_number = simpledialog.askstring("Hapus Riwayat Pasien", 
                            record_list + "\n\nMasukkan nomor urut rekam medis pasien untuk dihapus:")
                        
                        if record_number in record_numbers:
                            # Execute deletion command
                            delete_output = run_process(f'7 {id_pasien}\n {record_number} 0')
                            # Process delete_output if needed
                            messagebox.showinfo("Success", "Data riwayat pasien berhasil dihapus.")
                        else:
                            show_error_message("Nomor urut rekam medis tidak valid.", "Error")
                    else:
                        show_error_message("Tidak ada riwayat yang ditemukan untuk ID pasien ini.", "Error")
            else:
                show_error_message("Terjadi kesalahan saat menjalankan proses.", "Error")
        else:
            show_error_message("ID pasien tidak boleh kosong.", "Error")

    def cari_riwayat_pasien():
        nama_pasien = simpledialog.askstring("Input ID Pasien", "Masukkan ID Pasien:")
        if nama_pasien:
                # Execute process "9 {ID Pasien} 0"
                output = run_process(f"8 {nama_pasien}\n 0")
                if output:
                    if "Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan." in output:
                        show_error_message("Pasien tidak ditemukan.", "Error")
                    else:
                        # Regex to capture relevant output
                        messagebox.showinfo("Data Pasien", "Data ditemukan.")
                        result = re.search(r'Masukkan ID pasien: (.*?)Sistem Pencatatan Pasien Klinik X', output, re.DOTALL)
                        if result:
                            info_text = result.group(1).strip()
                            show_custom_message_large(info_text, "Informasi Pasien")
                        else:
                            show_custom_message_large("No matching text found.", "Informasi Pasien")
                else:
                    show_error_message("An error occurred while running the process.", "Error")

    # Initialize the main window
    root = tk.Tk()
    root.title("Aplikasi Klinik")
    root.geometry("300x320")  # Set window size

    # Create and place the title label
    title_label = tk.Label(root, text="Aplikasi Klinik", font=("Arial", 20))
    title_label.pack(pady=10)

    # Create buttons
    buttons = [
        "Ubah/Tambah Data Pasien",
        "Riwayat Pasien",
        "Informasi Pasien",
        "Laporan Pendapatan",
        "Laporan Pasien",
        "Daftar Pasien yang Perlu Kontrol",
        "Quit"
    ]

    for button in buttons:
        if button == "Quit":
            tk.Button(root, text=button, command=exit_program).pack(pady=5)
        else:
            tk.Button(root, text=button, command=lambda b=button: handle_click(b)).pack(pady=5)

    # Run the main loop
    root.mainloop()

if __name__ == '__main__':
    main()
