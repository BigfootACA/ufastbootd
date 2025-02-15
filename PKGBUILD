# Maintainer: BigfootACA <bigfoot@classfun.cn>

pkgname=ufastbootd
pkgver=r2.6705767
pkgrel=1
pkgdesc="Userspace Fastboot Daemon"
arch=(x86_64 i686 pentium4 arm armv6h armv7h aarch64)
url="https://github.com/BigfootACA/ufastbootd.git"
license=(LGPL-3.0-or-later)
makedepends=(git cmake)
depends=(util-linux-libs)
optdepends=(
	"systemd-gadget: for USB gadget setup"
)
source=(
	CMakeLists.txt
	ufastbootd.service
	dev-usb-ffs-fastboot.mount
)
md5sums=(SKIP SKIP SKIP)

pkgver(){
	dir="$(dirname "$(realpath "$srcdir/CMakeLists.txt")")"
	cnt="$(git -C "$dir" rev-list --count HEAD 2>/dev/null||true)"
	sha="$(git -C "$dir" rev-parse --short HEAD 2>/dev/null||true)"
	if [ -n "$cnt" ] && [ -n "$sha" ]; then
		printf "r%s.%s" "$cnt" "$sha"
	else
		printf "0.1"
	fi
}

build(){
	dir="$(dirname "$(realpath "$srcdir/CMakeLists.txt")")"
	cmake -S "$dir" -B build --install-prefix /usr
	cmake --build build
}

package() {
	DESTDIR="$pkgdir" cmake --install build
	install -Dm644 "$srcdir/ufastbootd.service" "$pkgdir/usr/lib/systemd/system/ufastbootd.service"
	install -Dm644 "$srcdir/dev-usb-ffs-fastboot.mount" "$pkgdir/usr/lib/systemd/system/dev-usb\\x2dffs-fastboot.mount"
}
